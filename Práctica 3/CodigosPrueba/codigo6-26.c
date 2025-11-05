/********************************************************************
* Francisco Almeida, Domingo Gim�nez, Jos� Miguel Mantas, Antonio M. Vidal:
* Introducci�n a la programaci�n paralela,
* Paraninfo Cengage Learning, 2008
*
* Cap�tulo 6,
* Secci�n 6.10 Trabajadores replicados: C�digo 6.26
* Soluci�n del problema de las reinas utilizando bolsa de tareas en OpenMP
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define N 12
#define THREADS 12

struct tarea {
  int s[N];
  int fila;
};

struct nodo {
  struct tarea t;
  struct nodo *sig;
};

void iniciar(struct nodo **d) {
  int i;

  *d = (struct nodo *) malloc(sizeof(struct nodo));

  for (i = 0; i < N; i++)
    (*d)->t.s[i] = -1;
  (*d)->t.fila = 0;
  (*d)->sig = NULL;
}

void escribirtarea (struct tarea tareaact) {
  int i;

  for (i = 0; i < tareaact.fila; i++)
    printf("%d ", tareaact.s[i]);
  printf("+\n");
}

void escribir(struct nodo *d) {
  int i;

  while (d != NULL) {
    escribirtarea(d->t);
    d = d->sig;
  }
  printf("*\n");
}

int vacia(struct nodo *d) {
  return d == NULL;
}

struct tarea extraer(struct nodo **d) {
  struct tarea tareaact;
  struct nodo *p;
  int i;

  for (i = 0; i < N; i++)
    tareaact.s[i] = (*d)->t.s[i];
  tareaact.fila = (*d)->t.fila;
  p = (*d);
  (*d) = (*d)->sig;
  free(p);
  return tareaact;
}

int valido(struct tarea tareaact, int col) {
  int i;

  for (i = 0; i < tareaact.fila; i++)
    if (tareaact.s[i]==col || tareaact.fila+col==tareaact.s[i]+i || col-tareaact.fila==tareaact.s[i]-i)
      return 0;
  return 1;
}

struct tarea ponerreina(struct tarea tareaact, int col) {
  int i;
  struct tarea nuevatarea;

  for (i = 0; i < tareaact.fila; i++)
    nuevatarea.s[i] = tareaact.s[i];
  nuevatarea.s[tareaact.fila] = col;
  for (i = tareaact.fila + 1; i < N; i++)
    nuevatarea.s[i] = -1;
  nuevatarea.fila = tareaact.fila+1;
  return nuevatarea;
}

void insertar(struct nodo **d, struct tarea nuevatarea) {
  struct nodo *temp;
  int i;

  temp = (struct nodo *) malloc(sizeof(struct nodo));
  for (i = 0; i < N; i++)
    temp->t.s[i] = nuevatarea.s[i];
  temp->t.fila = nuevatarea.fila;
  temp->sig = (*d);
  (*d) = temp;
}

void reinas(void) {
    struct nodo *bolsa;
    struct tarea tareaact;
    int i, fin, acabados, tareas, tomada, soluciones;
    iniciar(&bolsa);
    tareas = 1;
    omp_set_num_threads(THREADS);
// acabados indica el n�mero de threads que ha acabado su trabajo
    acabados = THREADS;
    #pragma omp parallel private(fin, tareaact, i, tomada)
    {
        fin = 0;
        while (!fin) {
// acceso en exclusi�n mutua a la bolsa de tareas
// y a las variables de control
            #pragma omp critical
            {
                fin = 0;
                tomada = 0;
// tomada indica si se ha tomado una tarea de la bolsa
                if (tareas == 0 && acabados == THREADS)
                    {
			fin=1;
			//escribirtarea(tareaact);//LUPE
		}

                else if(tareas != 0) {
                    acabados--;
                    tareas--;
                    tomada = 1;
                    tareaact = extraer(&bolsa);
                }
            }
            if (tomada) {
                for (i = 0; i < N; i++){

                    if (valido(tareaact, i)) {
                        if (tareaact.fila < (N-1)) {
                            #pragma omp critical
                            {
                                tareas++;
                                insertar(&bolsa, ponerreina(tareaact, i));
                            }
                        } else {

                            escribirtarea(ponerreina(tareaact, i));
#pragma omp critical
                            soluciones++;
                        }
                    }
		}//for
                #pragma omp critical
                    acabados++;
            }//if (tomada)
        }
    }
    printf("Soluciones: %d\n", soluciones);
}

int main(int argc,char *argv[]) {

  reinas();
    printf("fin\n");
}
