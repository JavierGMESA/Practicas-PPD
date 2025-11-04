#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORTBase 8080

int main(){
	int sock = 0;
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
	if(mensajeRecibido[0] == '1')
	{
		while(strcmp(mensajeEnviado, "FIN\n") != 0 && strcmp(mensajeRecibido, "FIN") != 0)
		{
			
			printf("\nUsted: ");
			strcpy(mensajeEnviado, "\0");
			fgets(mensajeEnviado, sizeof(mensajeEnviado), stdin);
			write(sock, mensajeEnviado, strlen(mensajeEnviado));
			if(strcmp(mensajeEnviado, "FIN\n") != 0)
			{
				strcpy(mensajeRecibido, "\0");
				int bytes = read(sock, mensajeRecibido, 1024);
				mensajeRecibido[bytes] = '\0';
				printf("\nEl otro: %s",mensajeRecibido);
			}
		}
	}
	else
	{
		while(strcmp(mensajeEnviado, "FIN\n") != 0 && strcmp(mensajeRecibido, "FIN") != 0)
		{
			
			strcpy(mensajeRecibido, "\0");
			int bytes = read(sock, mensajeRecibido, 1024);
			mensajeRecibido[bytes] = '\0';
			printf("El otro: %s\n",mensajeRecibido);
			if(strcmp(mensajeRecibido, "FIN") != 0)
			{
				printf("\nUsted: ");
				strcpy(mensajeEnviado, "\0");
				fgets(mensajeEnviado, sizeof(mensajeEnviado), stdin);
				write(sock, mensajeEnviado, strlen(mensajeEnviado));
			}
		}
	}


	

	
	close(sock);
	return 0;
}

