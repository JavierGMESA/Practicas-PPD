#include <stdio.h>
#include <omp.h>

int main ()  {
    int nthreads, tid;
    omp_set_num_threads(4);
    #pragma omp parallel private(tid)     // Expande un grupo de threads (tid es una variable privada)
                // Cada thread contiene sus propias copias de variables
    {
        tid = omp_get_thread_num();       // Obtiene el identificador del thread 
        nthreads = omp_get_num_threads(); // Obtiene el número de threads 
        if(tid == 0)                      //maestro es el 0
        {
            printf("Hola amigos, soy vuestro maestro\n");
        }
        else
        {
            printf("Hola maestro, soy el esclavo %i\n", tid);
        }
    }
    return 0;
}
