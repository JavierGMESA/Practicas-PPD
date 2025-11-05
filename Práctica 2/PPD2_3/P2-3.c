#include <stdio.h>
#include <omp.h>
#define N   20

int main () {
    int i, j, k, correct = 1;
    int nthreads, tid;
    int n, sum;
    int a1[N][N], a2[N][N], c[N][N], b[N][N];
    // Inicializa b, c, m, n
    n = N;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            b[i][j] = i + j;
            c[i][j] = i;
        }
    }
    
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++)
        {
            sum = 0;
            for(k = 0; k < N; ++k)
                sum += b[i][k] * c[k][j];
            a1[i][j] = sum;
        }
    }
    sum = 0;

    printf("Matriz resultado secuencial:\n");
    for(i = 0; i < n; ++i)
    {
        printf("[");
        for(j = 0; j < N; ++j)
        {
            printf(" %i ", a1[i][j]);
        }
        printf("]\n");
    }

    // Las variables a, b, c, m, n, nthreads son de tipo compartido
    // Las variables i, j, sum, tid son de tipo privado
    #pragma omp parallel for default(none) \
    private(tid, i, j, k, sum) shared(n, a2, b, c, nthreads)
    for (i = 0; i < n; i++) 
    {
        tid = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        for (j = 0; j < n; j++)
        {
            sum = 0;
            for(k = 0; k < N; ++k)
                sum += b[i][k] * c[k][j];
            a2[i][j] = sum;
        }
         
         printf("El thread %d, de %d threads, calcula la iteracion i = %d\n", tid, nthreads, i); 
    }

    printf("Matriz resultado paralelo:\n");
    for(i = 0; i < n; ++i)
    {
        printf("[");
        for(j = 0; j < N; ++j)
        {
            printf(" %i ", a2[i][j]);
        }
        printf("]\n");
    }

    i = 0;
    j = 0;
    while(i < N && correct)
    {
        while(j < N && correct)
        {
            if(a1[i][j] != a2[i][j])
            {
                correct = 0;
            }
            ++j;
        }
        ++i;
    }
    if(correct)
    {
        printf("Ejecucion OK...\n");
    }
    else
    {
        printf("Se ha producido un fallo\n");
    }
}