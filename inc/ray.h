
#ifndef RAY_H
#define RAY_H

#include "math_vec/methodes.h"

typedef struct Ray
{
	v3f	pos;
	v3f	dir;
} Ray;

typedef struct RayHit
{
	v3f		real_pos;
	float	dist;
	v3si	block_pos;
	v3si	normal;
	int		step;
} RayHit;

#endif
