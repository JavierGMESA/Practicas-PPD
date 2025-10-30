#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(){
	int sock = 0;
	struct sockaddr_in direccionServidor;
	char *mensaje = "Hola mundo";
	
	//Creamos el socket
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Error al crear el socket \n");
		return -1;
	}
	
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_port = htons(PORT);
	
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
	
	//Enviamos el mensaje
	write(sock, mensaje, strlen(mensaje));
	printf("Mensaje enviado\n");
	close(sock);
	return 0;
}

