#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "estado.h"

extern uint64_t **aleatorios;
extern int cantidad;
extern int filas;
extern int columnas;
extern int **tablero;
extern int *posicionx;
extern int *posiciony;

uint64_t calcZorbist(Estado *estado){
  uint64_t zorbist;
  int i = 0;
  // inicializamos zorbist
  switch (estado->naves[0]) {
    case 0:
    zorbist = aleatorios[0][0];
    break;
    case 1:
    zorbist = aleatorios[0][1];
    break;
    case 2:
    zorbist = aleatorios[0][2];
    break;
    case 3:
    zorbist = aleatorios[0][3];
    break;
    case 4:
    zorbist = aleatorios[0][4];
    break;
    case 5:
    zorbist = aleatorios[0][5];
    break;
  }
  i = 1;
  while (i < cantidad) {
    switch (estado->naves[i]) {
      case 0:
      zorbist ^= aleatorios[i][0];
      break;
      case 1:
      zorbist ^= aleatorios[i][1];
      break;
      case 2:
      zorbist ^= aleatorios[i][2];
      break;
      case 3:
      zorbist ^= aleatorios[i][3];
      break;
      case 4:
      zorbist ^= aleatorios[i][4];
      break;
      case 5:
      zorbist ^= aleatorios[i][5];
      break;
    }
    i++;
  }
  return zorbist;
}

Estado* Disparar(Estado *estado, int x, int y){

  //Actualizar Tablero
  for (int i = 0; i < cantidad; i++) {
    tablero[posiciony[i]][posicionx[i]] = estado->naves[i];
  }

  // Disparamos con la nave en posicion (x,y) y generamos el tablero del nuevo estado
  switch (tablero[y][x]) {
    // Apuntando hacia arriba
    case 0:
    for (int i = y-1; i > -1; i--) {
      if (tablero[i][x] < 3 || tablero[i][x] == 4) {
        tablero[i][x]++;
        break;
      }
      else if (tablero[i][x] == 3) {
        tablero[i][x] = 0;
        break;
      }
    }
    break;
    // Apuntando hacia la derecha
    case 1:
    for (int i = x+1; i < columnas; i++) {
      if (tablero[y][i] < 3 || tablero[y][i] == 4) {
        tablero[y][i]++;
        break;
      }
      else if (tablero[y][i] == 3) {
        tablero[y][i] = 0;
        break;
      }
    }
    break;
    // Apuntando hacia abajo
    case 2:
    for (int i = y+1; i < filas; i++) {
      if (tablero[i][x] < 3 || tablero[i][x] == 4) {
        tablero[i][x]++;
        break;
      }
      else if (tablero[i][x] == 3) {
        tablero[i][x] = 0;
        break;
      }
    }
    break;
    // Apuntando hacia la izquierda
    case 3:
    for (int i = x-1; i > -1; i--) {
      if (tablero[y][i] < 3 || tablero[y][i] == 4) {
        tablero[y][i]++;
        break;
      }
      else if (tablero[y][i] == 3) {
        tablero[y][i] = 0;
        break;
      }
    }
    break;
  }

  // Generamos nuevo estado
  Estado *nuevo = malloc(sizeof(Estado));
  nuevo->naves = malloc(sizeof(uint8_t)*cantidad);
  for (int i = 0; i < cantidad; i++) {;
    nuevo->naves[i] = tablero[posiciony[i]][posicionx[i]];
  }
  // nuevo->estado_anterior = estado;
  nuevo->zorbist = calcZorbist(nuevo);
  nuevo->x = x;
  nuevo->y = y;

  return nuevo;

}
