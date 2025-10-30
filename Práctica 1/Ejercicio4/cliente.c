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
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
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
	
	//Enviamos el mensaje
	sendto(sock, mensaje, strlen(mensaje), 0, (struct sockaddr_in *) & direccionServidor, sizeof(direccionServidor));
	printf("Mensaje enviado\n");
	close(sock);
	return 0;
}

