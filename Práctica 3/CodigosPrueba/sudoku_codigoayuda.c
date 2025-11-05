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

void iniciar(struct nodo **d) {
//COMPLETAR
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
}

void escribirtarea (struct tarea tareaact) {
//COMPLETAR
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

int valido(struct tarea tareaact, int nro) {
//COMPLETAR
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
}

int main(int argc, char *argv[]) {
   resolverSudoku();
}
