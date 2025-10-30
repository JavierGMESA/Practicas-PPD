#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORTBase 8080
#define SA struct sockaddr

int main(){
	int serverSocket, confirmacion1, confirmacion2;
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
	
	//Aceptamos las conexiones
	int len1 = sizeof(cli);
	if((confirmacion1 = accept(serverSocket, (SA*)&cli, &len1)) < 0 ){
		perror("Error al aceptar conexión");
		exit(EXIT_FAILURE);
	}
	printf("Cliente 1 conectado\n");

	int len2 = sizeof(cli);
	if((confirmacion2 = accept(serverSocket, (SA*)&cli, &len2)) < 0 ){
		perror("Error al aceptar conexión");
		exit(EXIT_FAILURE);
	}
	printf("Cliente 2 conectado\n");

	strcpy(mensajeEnviado, "1");
	write(confirmacion1, mensajeEnviado, strlen(mensajeEnviado));
	strcpy(mensajeEnviado, "2");
	write(confirmacion2, mensajeEnviado, strlen(mensajeEnviado));

	while(strcmp(mensajeEnviado, "FIN\n") != 0 && strcmp(mensajeRecibido, "FIN") != 0)
	{
		int bytes = read(confirmacion1, mensajeRecibido, 1024);
		mensajeRecibido[bytes-1] = '\0';
		strcpy(mensajeEnviado, mensajeRecibido);
		write(confirmacion2, mensajeEnviado, strlen(mensajeEnviado));
		if(strcmp(mensajeRecibido, "FIN") != 0)
		{
			int bytes = read(confirmacion2, mensajeRecibido, 1024);
			mensajeRecibido[bytes-1] = '\0';
			strcpy(mensajeEnviado, mensajeRecibido);
			write(confirmacion1, mensajeEnviado, strlen(mensajeEnviado));
		}
	}

	close(serverSocket);
	
}