#include <mpi.h> 
#include <stdio.h>

int main(int argc, char *argv[]) {
    int myrank, size, tag = 1;
    char mensaje[100];
    
    MPI_Status status;
    MPI_Init(&argc, &argv);                  // Inicializa el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);  // Número de identificación 
                                             // del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size);    // Número total de procesos 
    
    if(myrank == 0)
    {
        sprintf(mensaje, "Hola amigos, soy vuestro maestro\n");
        MPI_Bcast(mensaje, strlen(mensaje)+1, MPI_CHAR, 0, MPI_COMM_WORLD);
        for(int origen = 1; origen < size; ++origen)
        {
            MPI_Recv(mensaje, 100, MPI_CHAR, origen, tag,  MPI_COMM_WORLD, &status); 
            printf("%s\n", mensaje);
        }
    }
    else
    {
        MPI_Bcast(mensaje, 100, MPI_CHAR, 0, MPI_COMM_WORLD);
        printf("Mensaje proceso %d: %s\n", myrank, mensaje);
        sprintf(mensaje, "Hola maestro, soy el esclavo %i\n", myrank);
        MPI_Send(mensaje, strlen(mensaje) + 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();                          // Finaliza el entorno MPI
} 