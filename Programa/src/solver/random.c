#include "random.h"

uint64_t get_random_number()
{
  return (((uint64_t)pcg32_random()) << 32) + pcg32_random();
}
