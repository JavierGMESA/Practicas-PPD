#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#define PORTBase 8080
#define SA struct sockaddr

typedef struct {
    int A[3][3];
    int B[3][3];
    int C[3][3];
} SharedMatrices;


int main(){
	int serverSocket, confirmacion, pid, status, i, j;
	struct sockaddr_in direccion, cli;
	char mensajeRecibido[1024] = {0}, mensajeEnviado[1024] = {0};
	int a[3][3], b[3][3], c[3][3];

	//Creamos el socket
	if((serverSocket = socket(AF_INET, SOCK_STREAM, 0))==0){
		perror("Fallo al crear el socket");
		exit(EXIT_FAILURE);
	}
	printf("Socket creado\n");
	
	//Asignamos dirección y puerto
	direccion.sin_family = AF_INET;
	direccion.sin_addr.s_addr = INADDR_ANY;
	direccion.sin_port = htons( PORTBase );
	
	//Ligamos la dirección al socket
	if(bind(serverSocket, (struct sockaddr *)&direccion, sizeof(direccion))<0){
		perror("Fallao al vincular el socket");
		exit(EXIT_FAILURE);
	}
	printf("Socket bindeado\n");
	
	//Esperamos a que se conecte el cliente, indicando la cola máxima, en este caso, 3
	if(listen(serverSocket, 3) < 0){
		perror("Error al esperar la conexión");
		exit(EXIT_FAILURE);
	}
	printf("Socket escuchando\n");
	
	int len = sizeof(cli);
	if((confirmacion = accept(serverSocket, (SA*)&cli, &len)) < 0 ){
		perror("Error al aceptar conexión");
		exit(EXIT_FAILURE);
	}
	printf("Conexion con el cliente\n");

	read(confirmacion, a, sizeof(a));
	read(confirmacion, b, sizeof(b));

	printf("Matrices enviadas correctamente\n");

	/*
	int fd = shm_open("/matrices", O_CREAT, 0666);
	ftruncate(fd, sizeof(SharedMatrices));
	fd = shm_open("/matrices", O_RDWR, 0666);
	SharedMatrices *data = mmap(0, sizeof(SharedMatrices), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	printf("Memoria compartida creada\n");
	*/

	int fd = shm_open("/matrices", O_CREAT | O_RDWR, 0666);
	if (fd == -1) {
		perror("Error al crear memoria compartida");
		exit(EXIT_FAILURE);
	}

	if (ftruncate(fd, sizeof(SharedMatrices)) == -1) {
		perror("Error al dimensionar memoria compartida");
		exit(EXIT_FAILURE);
	}

	SharedMatrices *data = mmap(0, sizeof(SharedMatrices),
								PROT_READ | PROT_WRITE,
								MAP_SHARED, fd, 0);

	if (data == MAP_FAILED) {
		perror("Error al mapear memoria compartida");
		exit(EXIT_FAILURE);
	}

	printf("Memoria compartida creada y mapeada correctamente\n");

	for(i = 0; i < 3; ++i)
	{
		for(j = 0; j < 3; ++j)
		{
			data->A[i][j] = a[i][j];
			data->B[i][j] = b[i][j];
			data->C[i][j] = 0;
		}
	}

	printf("Memoria compartida seteada\n");

	for(i = 0; i < 3; ++i)
	{
		pid = fork();
		if(pid == 0)
		{
			for(j = 0; j < 3; ++j)
			{
				for(int k = 0; k < 3; ++k)
				{
					data->C[i][j] += data->A[i][k] * data->B[k][j];
				}
			}
			exit(0);
		}
	}

	for(int i = 0; i < 3; ++i)
	{
		pid = wait(&status);
	}

	printf("Hijos han terminado\n");

	for(i = 0; i < 3; ++i)
	{
		for(j = 0; j < 3; ++j)
		{
			c[i][j] = data->C[i][j];
		}
	}

	write(confirmacion, c, sizeof(c));
	
	shm_unlink("/matrices");

	close(serverSocket);
}