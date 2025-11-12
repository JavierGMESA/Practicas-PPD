#include <mpi.h> 
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int myrank, size;
    int i, j;
    int m[8][8], v[8], resS[8], resP[8], resParcialS = 0, resParcialP = 0;

    MPI_Init(&argc, &argv);                  // Inicializa el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);  // Número de identificación del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size);    // Número total de procesos 
    
    if(myrank == 0)
    {
        for(i = 0; i < 8; ++i)
        {
            for(j = 0; j < 8; ++j)
            {
                m[i][j] = rand() % 3;
            }
            v[i] = rand() % 3;
        }

        for(i = 0; i < 8; ++i)
        {
            for(j = 0; j < 8; ++j)
            {
                resParcialS += v[j] * m[i][j];
            }
            v[i] = resParcialS;
            resParcialS = 0;
        }

        
    }

    MPI_Finalize();                          // Finaliza el entorno MPI
} 