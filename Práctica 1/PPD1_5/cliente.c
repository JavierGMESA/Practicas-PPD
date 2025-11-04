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

	strcpy(mensajeRecibido, "\0");
	read(sock, mensajeRecibido, 1024);
	printf("%s",mensajeRecibido);
	unsigned numero = 0;
	scanf("%u", &numero);
	sprintf(mensajeEnviado, "%u", numero);
	write(sock, mensajeEnviado, strlen(mensajeEnviado));
	strcpy(mensajeRecibido, "\0");
	int bytes = read(sock, mensajeRecibido, 1024);
	mensajeRecibido[bytes] = '\0';
	unsigned puerto = atoi(mensajeRecibido);
	printf("\nEl puerto enviado es %u\n", puerto);

	close(sock);

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Error al crear el socket \n");
		return -1;
	}
	
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_port = htons(puerto);
	
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

	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	
	while(strcmp(mensajeEnviado, "FIN\n") != 0 && strcmp(mensajeRecibido, "FIN") != 0)
	{
		
		printf("\nIntroduzca el texto a enviar: ");
		strcpy(mensajeEnviado, "\0");
		fgets(mensajeEnviado, sizeof(mensajeEnviado), stdin);
		//Enviamos el mensaje al servidor
		write(sock, mensajeEnviado, strlen(mensajeEnviado));
		if(strcmp(mensajeEnviado, "FIN\n") != 0)
		{
			//Recibimos un mensaje del servidor
			strcpy(mensajeRecibido, "\0");
			int bytes = read(sock, mensajeRecibido, 1024);			//Leemos usando el mismo socket que utilizamos para comunicarnos con el servidor
			mensajeRecibido[bytes-1] = '\0';
			printf("El mensaje es: %s\n",mensajeRecibido);
		}
	}

	close(sock);
	return 0;
}

