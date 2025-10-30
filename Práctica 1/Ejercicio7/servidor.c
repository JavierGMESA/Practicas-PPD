#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/wait.h>
#define PORTBase 8080
#define SA struct sockaddr

int main(){
	int serverSocket, confirmacion, num_clientes = 0;
	struct sockaddr_in direccion, cli;
	char mensajeRecibido[1024] = {0}, mensajeEnviado[1024] = {0};

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
	
	while(1)
	{
		//Aceptamos las conexiones
		int len = sizeof(cli);
		if((confirmacion = accept(serverSocket, (SA*)&cli, &len)) < 0 ){
			perror("Error al aceptar conexión");
			exit(EXIT_FAILURE);
		}
		++num_clientes;
		printf("Cliente %i conectado\n", num_clientes);

		int pid = fork();
		if(pid == 0)
		{
			strcpy(mensajeEnviado, "Introduzca los operandos de la suma: ");
			write(confirmacion, mensajeEnviado, strlen(mensajeEnviado));
			read(confirmacion, mensajeRecibido, 1024);
			int op1 = atoi(mensajeRecibido);
			read(confirmacion, mensajeRecibido, 1024);
			int op2 = atoi(mensajeRecibido);
			int res = op1 + op2;
			sprintf(mensajeEnviado, "El resultado es: %u y usted es el cliente %i", res, num_clientes);
			write(confirmacion, mensajeEnviado, strlen(mensajeEnviado));
			
			close(confirmacion);
			exit(0);
		}
		else
		{
			close(confirmacion);
			// recoger procesos hijos terminados sin bloquear  (el -1 significa cualquiera)
        	while(waitpid(-1, NULL, WNOHANG) > 0);
		}
	}
	

	close(serverSocket);
}