#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORTBase 8080
#define SA struct sockaddr

int main(){
	int serverSocket, confirmacion, pids[11], num_servers = 0, status;
	struct sockaddr_in direccion, cli;
	char mensajeRecibido[1024] = {0}, mensajeEnviado[1024] = {0};
	
	printf("Introduzca el numero de servidores que desea iniciar: ");
	scanf("%i", &num_servers);
	num_servers = num_servers < 11 ? num_servers : 11;

	for(int i = 0; i < num_servers; ++i)
	{
		pids[i] = fork();
		if(pids[i] == 0)
		{
			//Creamos el socket
			if((serverSocket = socket(AF_INET, SOCK_STREAM, 0))==0){
				perror("\nFallo al crear el socket");
				exit(EXIT_FAILURE);
			}
			printf("\nSocket creado\n");
			
			//Asignamos dirección y puerto
			direccion.sin_family = AF_INET;
			direccion.sin_addr.s_addr = INADDR_ANY;
			direccion.sin_port = htons( PORTBase + i );
			
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
			printf("Socket escuchando del servidor %i\n", i);

			sleep(1);
			
			//Aceptamos las conexiones
			int len = sizeof(cli);
			if((confirmacion = accept(serverSocket, (SA*)&cli, &len)) < 0 ){
				perror("Error al aceptar conexión");
				exit(EXIT_FAILURE);
			}
			printf("Mensaje recibido del servidor %i\n", i);

			if(i != 0)
			{
				while(strcmp(mensajeEnviado, "FIN\n") != 0 && strcmp(mensajeRecibido, "FIN") != 0)
				{
					int c;
					while ((c = getchar()) != '\n' && c != EOF);
					//Leemos el mensaje del cliente
					strcpy(mensajeRecibido, "\0");
					int bytes = read(confirmacion, mensajeRecibido, 1024);
					mensajeRecibido[bytes-1] = '\0';
					printf("El mensaje es: %s\n",mensajeRecibido);
					if(strcmp(mensajeRecibido, "FIN") != 0)
					{
						//Le escribimos un mensaje al cliente
						printf("\nIntroduzca el texto a enviar: ");
						strcpy(mensajeEnviado, "\0");
						fgets(mensajeEnviado, sizeof(mensajeEnviado), stdin);
						write(confirmacion, mensajeEnviado, strlen(mensajeEnviado));
					}
				}
			}
			else
			{
				strcpy(mensajeEnviado, "Introduzca el el servidor al que quiera conectarse: ");
				write(confirmacion, mensajeEnviado, strlen(mensajeEnviado));
				read(confirmacion, mensajeRecibido, 1024);
				unsigned numero = atoi(mensajeRecibido);
				numero = numero > 0 ? numero: 1;
				numero = numero < num_servers ? numero : num_servers;
				strcpy(mensajeEnviado, "\0");
				sprintf(mensajeEnviado, "%u", PORTBase + numero);
				write(confirmacion, mensajeEnviado, strlen(mensajeEnviado));
			}
			
			close(serverSocket);
			exit(0);
		}
	}
	for(int i = 0; i < num_servers; ++i)
	{
		int pid = wait(&status);
		printf("El servidor %i ha finalizado", pid);
	}
	
}