#include <stdlib.h>
#define N 9
#define THREADS 4

struct tarea {
  int s[N][N];
  int fila;
  int col;
};

struct nodo {
  struct tarea t;
  struct nodo *sig;
};

int buscaCeldaVacia(int s[N][N], int *x,int *y)
{
	for(*x;(*x)<N;(*x)++)
	{

		for(*y;(*y)<N;(*y)++)
		{
			if(s[*x][*y] == 0)
				{
					return 1;
				}
		}
		*y = 0;
	}
	return 0;
}

void iniciar(struct nodo **d) 
{
    //COMPLETAR
    int i, j;
    int x=0, y=0;
    *d = (struct nodo *) malloc(sizeof(struct nodo));

    int sudoku[9][9] =
    {
    {6,0,1,0,0,4,0,8,0},
    {0,4,9,7,3,0,0,0,0},
    {8,2,3,0,0,0,0,4,0},
    {0,0,4,0,0,0,0,0,6},
    {0,0,7,0,0,0,2,0,0},
    {9,8,0,0,0,0,3,0,0},
    {4,1,0,0,0,0,0,6,5},
    {0,0,0,0,4,1,8,3,0},
    {0,5,0,2,0,0,4,0,7}
    };

    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
        {
            (*d)->t.s[i][j] = sudoku[i][j];
        }
    }
    buscaCeldaVacia((*d)->t.s, &x, &y);
    (*d)->t.fila = x;
    (*d)->t.col = y;
}

void escribirtarea (struct tarea tareaact) 
{
    //COMPLETAR
    int i, j;
    printf("Posible solución:\n");
    for(i = 0; i < N; ++i)
    {
        printf("{");
        for(j = 0; j < N - 1; ++j)
        {
            printf("%d,", tareaact.s[i][j]);
        }
        printf("%d}\n", tareaact.s[i][8]);
    }
    printf("\n");
}

void escribir(struct nodo *d) {
  int i;
  while (d != NULL) {
    escribirtarea(d->t);
    d = d->sig;
  }
}

int vacia(struct nodo *d) {
  return d == NULL;
}

struct tarea extraer(struct nodo **d) {
  struct tarea tareaact;
  struct nodo *p;
  int i,j;

  for (i = 0; i < N; i++)
   for (j = 0; j < N; j++)
    tareaact.s[i][j] = (*d)->t.s[i][j];
  tareaact.fila = (*d)->t.fila;
  tareaact.col = (*d)->t.col;
  p = (*d);
  (*d) = (*d)->sig;
  free(p);
  return tareaact;
}

int valido(struct tarea tareaact, int nro) 
{
    //COMPLETAR
    int i, j;
    int FilaComienzo = tareaact.fila / 3 * 3;
    int ColumnaComienzo = tareaact.col / 3 * 3;


    if(tareaact.s[tareaact.fila][tareaact.col] != 0)
    {
        return 0;
    }
    else
    {
        for(i = 0; i < N; ++i)
        {
            if(tareaact.s[tareaact.fila][i] == nro || tareaact.s[i][tareaact.col] == nro)
            {
                return 0;
            }
        }
    }

    for(i = 0; i < 3; ++i)
    {
        for(j = 0; j < 3; ++j)
        {
            if(tareaact.s[FilaComienzo + i][ColumnaComienzo + j] == nro)
            {
                return 0;
            }
        }
    }
    return 1;
}

struct tarea ponerNumero(struct tarea tareaact, int nro) {
  int i,j;
  struct tarea nuevatarea;

  for (i = 0; i < N; i++)
  	for (j = 0; j < N; j++)
    	  nuevatarea.s[i][j] = tareaact.s[i][j];
  nuevatarea.s[tareaact.fila][tareaact.col] = nro;
  if (tareaact.col<8)
  {
  	nuevatarea.fila=tareaact.fila;
  	nuevatarea.col=tareaact.col+1;
  }
  else if (tareaact.fila<8)
  {
  	nuevatarea.fila=tareaact.fila+1;
  	nuevatarea.col=0;
  }
  else
  {
  	nuevatarea.fila=8;
  	nuevatarea.col=8;
  }

  return nuevatarea;
}

void insertar(struct nodo **d, struct tarea nuevatarea) {
  struct nodo *temp;
  int i,j;

  temp = (struct nodo *) malloc(sizeof(struct nodo));
  for (i = 0; i < N; i++)
   for (j = 0; j < N; j++)
    temp->t.s[i][j] = nuevatarea.s[i][j];
  temp->t.fila = nuevatarea.fila;
  temp->t.col = nuevatarea.col;
  temp->sig = (*d);
  (*d) = temp;
}

void resolverSudoku() {
    struct nodo *bolsa;
    struct tarea tareaact, nuevaTarea;
    int i,acabados,fin,tareas,tomada;
	int fila,col;
	char c;
	int hayVacia;

    iniciar(&bolsa);
    tareas=1;
    omp_set_num_threads (THREADS);
    acabados=THREADS;

    //COMPLETAR
    #pragma omp parallel private(fin, tareaact, i, tomada, hayVacia)
    {
        fin = 0;
        while (!fin) 
        {
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
                    hayVacia = buscaCeldaVacia(tareaact.s, &tareaact.fila, &tareaact.col);
                }
            }
            if(tomada) 
            {
                if(hayVacia)
                {
                    for (i = 1; i < N + 1; i++)
                    {
                        if (valido(tareaact, i)) 
                        {
                            #pragma omp critical
                            {
                                tareas++;
                                insertar(&bolsa, ponerNumero(tareaact, i));
                            }
                        }
                    }//for
                }
                else
                {
                    escribirtarea(ponerNumero(tareaact, i));
                }
                #pragma omp critical
                    acabados++;
            }//if (tomada)
        }
    }
    //printf("Soluciones: %d\n", soluciones);
}

int main(int argc, char *argv[]) {
   resolverSudoku();
}