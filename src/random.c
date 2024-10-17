
#include "random.h"

static __thread uint32_t randseed = 0x42424242;

void my_srand_u32(uint32_t a)
{
	randseed = a;
}

uint32_t my_rand_u32()
{
	randseed = (randseed ^ 61) ^ (randseed >> 16);
	randseed = randseed + (randseed << 3);
	randseed = randseed ^ (randseed >> 4);
	randseed = randseed * 0x27d4eb2d;
	randseed = randseed ^ (randseed >> 15);
	return (randseed);
}

uint32_t my_rand_u32_arg(uint32_t setseed)
{
	setseed = (setseed ^ 61) ^ (setseed >> 16);
	setseed = setseed + (setseed << 3);
	setseed = setseed ^ (setseed >> 4);
	setseed = setseed * 0x27d4eb2d;
	setseed = setseed ^ (setseed >> 15);
	return (setseed);
}
