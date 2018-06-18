#include <inttypes.h>
typedef struct Estado{
  // int **tablero;
  // int **disparos;
  // int cantidad_disparos;
  uint8_t x;
  uint8_t y;
  uint64_t zorbist; // xor de estado y posicion en hash
  uint8_t *naves; // arreglo valores de las celdas de las naves
  struct Estado *estado_anterior;
}Estado;
// Calcula el valor zorbist del estado
uint64_t calcZorbist(Estado *estado);

// Accion disparar
Estado* Disparar(Estado *estado, int x, int y);
