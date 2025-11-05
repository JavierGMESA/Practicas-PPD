/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 3, Código 3.16
* Cálculo de PI en OpenMP
*********************************************************************/
/*
#include <stdio.h>
#include <math.h>
#include <omp.h>

double f(double x) {
  return sqrt(1 - pow(x, 2.));
}

int main(int argc, char *argv[]) {
    int  n, i;
    double PI25DT = 3.141592653589793238462643;
    double pi, h, sum, x;

    printf("Numero de intervalos a usar: ");
    scanf("%d",&n);
    // Inicializa el número de intervalos a n
    h   = 1.0 / (double) n;
    sum = 0.0;
            // La variable pi es una variable de reducción mediante suma
    #pragma omp parallel for reduction(+:pi) private(x, i)
    for (i = 1; i <= n; i ++) {
        x = h * ((double)i - 0.5);
        pi += f(x);
    }
    pi = 4. * h * pi;
    printf("\npi es aproximadamente %.16f, el error es %.16f\n", pi, fabs(pi - PI25DT)); 
}
*/

/********************************************************************
* Guadalupe Ortiz Bellot
*
* Calculo de un área con OpenMP
*********************************************************************/

#include <stdio.h>
#include <math.h>
#include <omp.h>


int main(int argc, char *argv[]) {
    int  i, h, base, area, tid;
		int bases[10]={1,2,3,4,5,6,7,8,9,10};
    int total_base=0;
    int n=10; 

    h = 2;
 
    // La variable total_base es una variable de reducción mediante suma, es decir, una vez que todos los hilos
    // terminen con sus iteraciones, openMP se encargará de combinar los total_base parciales utilizando la operación
    // indicada (la + en este caso)
    #pragma omp parallel for reduction(+:total_base) private(i,tid)
    for (i = 0; i < n; i ++) {
        tid = omp_get_thread_num();
        total_base += bases[i];
	printf("El thread %d calcula la iteracion i = %d\n", tid, i);
    }
    area = total_base * h ;
    printf("El valor del área es %d\n", area ); 
}


