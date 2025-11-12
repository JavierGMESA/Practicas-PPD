#include <mpi.h> 
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int myrank, size;
    int i, j;
    int m[8][8], v[8];
    int mt[8][8], vcolumnas[16], vParcial[2], resS[8], resP[8], resParcialS = 0, resParcialP = 0;
    short correcto = 1;

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
                resParcialS += v[j] * m[j][i];
            }
            resS[i] = resParcialS;
            resParcialS = 0;
        }

        printf("El resultado de la multiplicación secuencial es: {");
        for(i = 0; i < 7; ++i)
        {
            printf("%i, ", resS[i]);
        }
        printf("%i}\n", resS[7]);

        if(size == 4)
        {
            MPI_Bcast(v, 8, MPI_INT, 0, MPI_COMM_WORLD);
            //Obtenemos la matriz traspuesta para poder distribuir las columnas
            for(i = 0; i < 8; ++i)
            {
                for(j = 0; j < 8; ++j)
                {
                    mt[i][j] = m[j][i];
                }
            }

            MPI_Scatter(mt, 16, MPI_INT, vcolumnas, 16, MPI_INT, 0, MPI_COMM_WORLD);     //sendcount son el número de elementos QUE RECIBIRÁ CADA PROCESO
            printf("Soy el proceso %d y voy a realizar la multiplicacion con las columnas %d y %d\n", myrank, myrank * 2, myrank * 2 + 1);
            for(i = 0; i < 2; ++i)
            {
                for(j = 0; j < 8; ++j)
                {
                    resParcialP += v[j] * vcolumnas[i * 8 + j];
                }
                vParcial[i] = resParcialP;
                resParcialP = 0;
            }
            MPI_Gather(vParcial, 2, MPI_INT, resP, 2, MPI_INT, 0, MPI_COMM_WORLD);       //En el Gather, al igual que en el Scatter, sendcount y recvcount deben ser iguales
            printf("El resultado de la multiplicación con MPI es: {");
            for(i = 0; i < 7; ++i)
            {
                printf("%i, ", resP[i]);
                if(resP[i] != resS[i])
                {
                    correcto = 0;
                }
            }
            printf("%i}\n", resP[7]);
            if(resP[7] != resS[7])
            {
                correcto = 0;
            }
            if(!correcto)
            {
                printf("Se ha producido un fallo\n");
            }
            else
            {
                printf("Ejecucion OK...\n");
            }
        }
        else
        {
            printf("Deben lanzarse 4 procesos exactamente!\n");
        }
    }
    else
    {
        if(size == 4)
        {
            MPI_Bcast(v, 8, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Scatter(NULL, 16, MPI_INT, vcolumnas, 16, MPI_INT, 0, MPI_COMM_WORLD);
            printf("Soy el proceso %d y voy a realizar la multiplicacion con las columnas %d y %d\n", myrank, myrank * 2, myrank * 2 + 1);
            for(i = 0; i < 2; ++i)
            {
                for(j = 0; j < 8; ++j)
                {
                    resParcialP += v[j] * vcolumnas[i * 8 + j];
                }
                vParcial[i] = resParcialP;
                resParcialP = 0;
            }
            MPI_Gather(vParcial, 2, MPI_INT, resP, 2, MPI_INT, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();                          // Finaliza el entorno MPI
} 