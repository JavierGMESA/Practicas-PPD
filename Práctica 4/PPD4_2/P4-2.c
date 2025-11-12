#include <mpi.h> 
#include <stdio.h>

int main(int argc, char *argv[]) {
    int myrank, size, i, tag = 1;
    int v1[10] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};
    int v2[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int resS = 0, resP = 0, resParcial = 0;
    int base, resto;
    MPI_Status status;

    MPI_Init(&argc, &argv);                  // Inicializa el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);  // Número de identificación del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size);    // Número total de procesos 

    for( i = 0; i < 10; ++i)
    {
        resS += v1[i] * v2[i];
    }
    if(myrank == 0)
    {
        printf("El resultado secuencial es %i\n", resS);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    
    if(size <= 10)
    {
        base = 10 / size;
        resto = 10 % size;
    }
    else
    {
        base = 1;
        resto = 0;
    }

    if(myrank == 0)
    {
        printf("El proceso 0 procesa desde el indice %d hasta el indice %d\n", 0, base + resto - 1);
        for(i = 0; i < base + resto; ++i)
        {
            resParcial += v1[i] * v2[i];
        }
        resP += resParcial;
        for(int origen = 1; origen < size; ++origen)
        {
            MPI_Recv(&resParcial, 1, MPI_INT, origen, tag, MPI_COMM_WORLD, &status);
            resP += resParcial;
        }

        printf("El resultado con MPI es %i\n", resP);
        if(resS == resP)
        {
            printf("Ejecucion OK...\n");
        }
        else
        {
            printf("Se ha producido un fallo\n");
        }
    }
    else if(myrank < 10)
    {
        printf("El proceso %d procesa desde el indice %d hasta el indice %d\n", myrank, myrank * base + resto, (myrank+1) * base + resto - 1);
        for(i = myrank * base + resto; i < (myrank+1) * base + resto; ++i)
        {
            resParcial += v1[i] * v2[i];
        }
        MPI_Send(&resParcial, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Send(&resParcial, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();                          // Finaliza el entorno MPI
} 