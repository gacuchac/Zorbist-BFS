#include "pcg_basic.h"

/** Generates a random double in the interval [0, bound] */
double random_bounded_double(double bound)
{
		double random = pcg32_random();
		random /= UINT32_MAX;
		return random * bound;
}

/** Sets an integer as random seed */
void   random_seed(int seed)
{
	pcg32_srandom((0x853c49e6748fea9bULL ^ seed) | 1, 0xda3e39cb94b95bdbULL);
}
