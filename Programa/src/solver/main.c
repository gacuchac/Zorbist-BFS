#include <stdio.h>
#include <stdlib.h>
#include "random.h"
#include <inttypes.h>
#include <time.h>
#include "estado.h"

uint64_t **aleatorios = NULL;
int *buscar_estados; // Se agregan estados segun posicion
Estado **revisar_estados; // Estados a revisar
int *posicionx = NULL;
int *posiciony = NULL;
int cantidad;
int filas;
int columnas;
int **tablero = NULL;

int main(int argc, char** argv)
{
	clock_t t = clock();
	if (argc != 2)
	{
		printf("Modo de uso: ./solver test.txt\n");
		 	return 0;
	}

	int maximo = 10000011;
	buscar_estados = calloc(maximo, sizeof(int));
	revisar_estados = (Estado **)calloc(maximo, sizeof(Estado*));
	for (int i = 0; i < maximo; i++) {
		buscar_estados[i] = 0;
		revisar_estados[i] = (Estado*)malloc(sizeof(Estado));
	}
	int **disparos = calloc(1000, sizeof(int*));
	for (int i = 0; i < 1000; i++) {
		disparos[i] = calloc(2,sizeof(int));
	}
	int cant_disparos = 0;

	FILE* file = fopen (argv[1], "r");
  int i = 0;
	fscanf (file, "%i", &i);
	int y = i;
	filas = y;
	fscanf (file, "%i", &i);
	int x = i;
	columnas = x;

	int total = x*y;

	// Crear tablero inicial
	tablero = malloc(y*(sizeof(int*)));
	for(int i = 0; i < y; i++)
	{
	    tablero[i] = (int*)malloc(sizeof(int)*x);
	}

	// Poblar tablero
	int j = 0;
	cantidad = 0;
  while (j < total)
    {
      fscanf (file, "%i", &i);
			int posy = (int) j/x;
			int posx = (int) j%x;
			tablero[posy][posx] = i;
			if (i < 5) {
					cantidad++;
				}
			j++;
    }
  fclose (file);

	// Arreglo de naves para crear estados
	uint8_t *naves = malloc(sizeof(uint8_t)*cantidad);
	// int *aux_naves = (int*)malloc(sizeof(int)*cantidad);
	posicionx = (int*)malloc(sizeof(int)*cantidad);
	posiciony = (int*)malloc(sizeof(int)*cantidad);
	int pos = 0;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (tablero[i][j] < 5) {
				naves[pos] = tablero[i][j];
				posiciony[pos] = i;
				posicionx[pos] = j;
				pos++;
			}
		}
	}

	// Creamos el arreglo de random
	aleatorios = (uint64_t**)malloc(cantidad*(sizeof(uint64_t*)));
	for(int k = 0; k < cantidad; k++)
	{
	    aleatorios[k] = (uint64_t*)malloc(sizeof(uint64_t)*6);
	}
	srand(time(NULL));
	for (int l = 0; l < cantidad; l++) {
		for (int m = 0; m < 6; m++) {
			aleatorios[l][m] = (((uint64_t)rand())<<32) + rand();
		}
	}

	// Creamos el primer estado
	Estado *inicial = malloc(sizeof(Estado));
	inicial->naves = naves;
	uint64_t zorb = calcZorbist(inicial);
	inicial->zorbist = zorb;

	Estado *nuevo_estado;
	Estado *estado_revisando;
	int termino = 1;
	int cant_estados = 0;
	int revisando = 0;
	int posestado = inicial->zorbist%maximo;
	buscar_estados[posestado] = 1;
	revisar_estados[cant_estados] = inicial;

	// Disparamos cada nave
	while (termino) {
		// Revisar siguiente estado de revisar
		estado_revisando = revisar_estados[revisando];
		for (int i = 0; i < cantidad; i++) {
			// Si la nave i no es asteroide, dispararla
			if (estado_revisando->naves[i] < 4) {
				nuevo_estado = Disparar(estado_revisando, posicionx[i], posiciony[i]);

				// Revisamos si se eliminaron todas las naves enemigas
				termino = 0;
				for (int j = 0; j < cantidad; j++) {
					if (nuevo_estado->naves[j] == 4) {
						termino = 1;
					}
				}

				// Buscamos si el estado existe y si no, lo agregamos a nuestra collecion y la siguiente busqueda
				posestado = nuevo_estado->zorbist%maximo;
				// printf("posestado: %i", posestado);
				if (buscar_estados[posestado] == 0) {
					nuevo_estado->estado_anterior = estado_revisando;
					// Revisamos si termino
					if (termino == 0) {
						Estado *padre = nuevo_estado;

						do  {
							disparos[cant_disparos][0] = padre->x;
							disparos[cant_disparos][1] = padre->y;
							cant_disparos++;
							padre = padre->estado_anterior;
						} while (padre->zorbist != inicial->zorbist);

						// printf("cantidad_disparos: %i\n", cant_disparos);
						while (cant_disparos > 0) {
							printf("%i,%i\n", disparos[cant_disparos-1][0],disparos[cant_disparos-1][1]);
							cant_disparos--;
						}
						t = clock() - t;
						// printf("%f\n",((float)t)/CLOCKS_PER_SEC);
						return 0;
					}
					buscar_estados[posestado] = 1;
					cant_estados++;
					revisar_estados[cant_estados] = nuevo_estado;
				}
			}
		}
		revisando++;
	}
// printf("cant_estados: %i\n", cant_estados);
	return 0;
}
