#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define PORTBase 8080

int main(){
	int sock = 0, i, j;
	struct sockaddr_in direccionServidor;
	char mensajeRecibido[1024] = {0}, mensajeEnviado[1024] = {0};
	int a[3][3], b[3][3], c[3][3];
	srand(time(NULL));
	
	
	//Creamos el socket
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Error al crear el socket \n");
		return -1;
	}
	
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_port = htons(PORTBase);
	
	//Transformar el IPv4 o 6 en un texto binario
	if(inet_pton(AF_INET, "127.0.0.1", &direccionServidor.sin_addr) <= 0){
		printf("\n Direccion invalida o no soportada \n");
		return -1;
	}
			
	//Conectar con el servidor
	if(connect(sock, (struct sockaddr *)&direccionServidor, sizeof(direccionServidor)) < 0){
		printf("\nConexion fallida\n");
		return -1;
	}

	for(i = 0; i < 3; ++i)
	{
		for(j = 0; j < 3; ++j)
		{
			a[i][j] = (rand() % 3) + 1;
			b[i][j] = (rand() % 3) + 1;
		}
	}

	printf("a = \n");
	for(i = 0; i < 3; ++i)
	{
		printf("[");
		for(j = 0; j < 3; ++j)
		{
			printf(" %i ", a[i][j]);
		}
		printf("]\n");
	}
	printf("b = \n");
	for(i = 0; i < 3; ++i)
	{
		printf("[");
		for(j = 0; j < 3; ++j)
		{
			printf(" %i ", b[i][j]);
		}
		printf("]\n");
	}

	write(sock, a, sizeof(a));
	write(sock, b, sizeof(b));
	read(sock, c, sizeof(c));

	printf("c = \n");
	for(i = 0; i < 3; ++i)
	{
		printf("[");
		for(j = 0; j < 3; ++j)
		{
			printf(" %i ", c[i][j]);
		}
		printf("]\n");
	}
	
	close(sock);
	return 0;
}

