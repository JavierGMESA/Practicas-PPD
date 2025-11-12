/********************************************************************
* Francisco Almeida, Domingo Giménez, José Miguel Mantas, Antonio M. Vidal:
* Introducción a la programación paralela,
* Paraninfo Cengage Learning, 2008
*
* Capítulo 3, Código 3.7
* Cálculo de PI en MPI
*********************************************************************/

#include <mpi.h>
#include <stdio.h>
#include <math.h>

/*double fabs(double);

double f(double a) {
    return (4.0 / (1.0 + a * a));
    }

int main(int argc, char *argv[]) {
    int  n, myid, numprocs, i;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;
    int source, dest, tag = 100;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
 
    printf("\nProcess %d of %d", myid, numprocs);
    n = 100;
    h = 1.0 / (double) n;
    sum = 0.0; // Suma de intervalos 
    for (i = myid + 1; i <= n; i += numprocs) {
        x = h * ((double)i - 0.5);
        sum += f(x);
    }
    mypi = h * sum;
    printf("\nProcessor: %d, mypi: %.16f\n", myid, mypi);
    if(myid == 0) {
        pi = mypi;
        for (i = 1; i < numprocs; i++) {
            source = i;        // Recibe resultados del resto de procesos 
            MPI_Recv(&mypi, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &status);
            pi += mypi;
        }
        printf("\npi es aproximadamente %.16f, el error cometido es %.16f", pi, fabs(pi - PI25DT));
    } else {
        dest = 0;
        // Envía cálculo local al proceso 0  
        MPI_Send(&mypi, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}*/

/********************************************************************
* Guadalupe Ortiz Bellot
*
* Calculo de un área con OpenMPI
*********************************************************************/

int main(int argc, char *argv[]) {
    int  n, myid, numprocs, i;

    int mi_area, area, h, total_base;
    int bases[10]={1,2,3,4,5,6,7,8,9,10};

    h = 2;
    int source, dest, tag = 100;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    total_base=0;
    n=10; 
 
    for (i = myid ; i < n; i += numprocs) {
        total_base += bases[i];
	  printf("El thread %d calcula la iteracion i = %d\n", myid, i);
    }
    mi_area = total_base * h ;
    printf("\nProcessor: %d, mi_area: %.d\n", myid, mi_area);

    if(myid == 0) {
        area = mi_area;
        for (i = 1; i < numprocs; i++) {
            source = i;        // Recibe resultados del resto de procesos 
            MPI_Recv(&mi_area, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
            area += mi_area;
        }
        printf ("\n**********TOTAL: %d *********************\n",area);
    } else {
        dest = 0;
        // Envía cálculo local al proceso 0  
        MPI_Send(&mi_area, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
