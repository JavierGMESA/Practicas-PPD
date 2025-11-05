#include <stdio.h>
#include <omp.h>
#define CHUNKSIZE 2
#define N    10

int main () {
    int i, chunk;
    int nthreads, tid;
    int a[N], b[N], sum1 = 0, sum2 = 0;
    // Algunas inicializaciones
    for (i = 0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    chunk = CHUNKSIZE;              //Numero de iteraciones que le corresponden a cada thread 

    //Secuencial
    for(i = 0; i < N; ++i)
    {
        sum1 += a[i] * b[i];
    }

    printf("El resultado secuencial es %d\n", sum1);

    //Paralelo
    // Las variables a, b, c, chunk son de tipo compartido
    // Las variables i, tid  son privadas a cada thread
    #pragma omp parallel shared(a, b, chunk) private(i, tid) reduction(+:sum2)
    {
        // Se realiza una asignación estática de iteraciones
        // en la que el tamaño del bloque se fija a chunk
        #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++) {
            tid = omp_get_thread_num();
            nthreads = omp_get_num_threads();
            sum2 += a[i] * b[i];
            printf("El thread %d, de %d threads, calcula la iteracion i =%d\n", tid, nthreads, i); 
        }
    }  // Fin de la región paralela

    printf("El resultado paralelo es %d\n", sum2);

    if(sum1 == sum2)
    {
        printf("Ejecucion OK...\n");
    }
    else
    {
        printf("Se ha producido un fallo\n");
    }
}