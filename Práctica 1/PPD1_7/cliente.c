#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORTBase 8080

int main(){
	int sock = 0, op1, op2;
	struct sockaddr_in direccionServidor;
	char mensajeRecibido[1024] = {0}, mensajeEnviado[1024] = {0};
	unsigned num_server = 0;
	
	
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

	read(sock, mensajeRecibido, 1024);
	printf("%s", mensajeRecibido);
	scanf("%i", &op1);
	sprintf(mensajeEnviado, "%i", op1);
	write(sock, mensajeEnviado, strlen(mensajeEnviado));
	scanf("%i", &op2);
	sprintf(mensajeEnviado, "%i", op2);
	write(sock, mensajeEnviado, strlen(mensajeEnviado));
	printf("\n");
	read(sock, mensajeRecibido, 1024);
	printf("%s", mensajeRecibido);
	
	close(sock);
	return 0;
}

