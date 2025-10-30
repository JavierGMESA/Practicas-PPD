#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#define SA struct sockaddr

int main(){
	int serverSocket, confirmacion;
	struct sockaddr_in direccion, cli;
	char mensaje[1024] = {0};
	
	//Creamos el socket
	if((serverSocket = socket(AF_INET, SOCK_STREAM, 0))==0){
		perror("Fallo al crear el socket");
		exit(EXIT_FAILURE);
	}
	printf("Socket creado\n");
	
	//Asignamos dirección y puerto
	direccion.sin_family = AF_INET;
	direccion.sin_addr.s_addr = INADDR_ANY;
	direccion.sin_port = htons( PORT );
	
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
	int len = sizeof(cli);
	if((confirmacion = accept(serverSocket, (SA*)&cli, &len)) < 0 ){
		perror("Error al aceptar conexión");
		exit(EXIT_FAILURE);
	}
	printf("Mensaje recivido\n");
	//Leemos el mensaje del cliente
	read(confirmacion, mensaje, 1024);
	printf("%s\n",mensaje);
	close(serverSocket);
}