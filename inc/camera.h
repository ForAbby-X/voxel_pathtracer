
#ifndef CAMERA_H
#define CAMERA_H

#include "math_vec/types.h"

typedef struct Camera
{
	v3f		pos;
	v2f		rot;
	float	fov;
} Camera;

#endif
