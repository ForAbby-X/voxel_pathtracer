
#ifndef MATH_VEC_METHODES_H
# define MATH_VEC_METHODES_H

/*
 *	typedef char			v2sc __attribute__((vector_size(2)));
 *	typedef unsigned char	v2uc __attribute__((vector_size(2)));
 *	
 *	typedef int				v2si __attribute__((vector_size(8)));
 *	typedef unsigned int	v2ui __attribute__((vector_size(8)));
 *	
 *	typedef long			v2sl __attribute__((vector_size(8)));
 *	typedef unsigned long	v2ul __attribute__((vector_size(8)));
 *	
 *	typedef float			v2f __attribute__((vector_size(8)));
 *	
 *	typedef double			v2d __attribute__((vector_size(16)));
 */
#include "math_vec/types.h"
#include <math.h>

/*
 *	Will add the macro to choose from the best function type automatically.
 *	(At compile time.)
 *
 *	Todo: do it !
 *
 *	Alan De Freitas - 21:25 Sep 15 2024
 */

/* * _V2 - macro * */
// #define __v2_math(TYPE, OPX) ( TYPE##_##OPX )
// #define _v2_math(OP, X) __v2_math(typeof(X), OP##X)

/* * V2 - macro * */
// #define v2_swap(X) _v2_math(swap, X)

// #define v2_swap(vec) ({ (typeof((vec))){(vec)[1], (vec)[0]}; })

// #define v2_sum(vec) ({ (vec)[0] + (vec)[1]; })
// #define v2_sub(vec) ({ (vec)[0] - (vec)[1]; })
// #define v2_mul(vec) ({ (vec)[0] * (vec)[1]; })
// #define v2_div(vec) ({ (vec)[0] / (vec)[1]; })

// #define v2_mag(vec) ({ sqrtf(v2_sum((vec) * (vec))); })
// #define v2_norm(vec) ({ (vec) / v2_mag((vec)); })

// #define v2_dot(vec_a, vec_b) ({ v2_sum((vec_a) * (vec_b)); })
// #define v2_cross(vec_a, vec_b) ({ v2_sub((vec_a) * v2_swap((vec_b))); })

// #define v2_rot(vec, ang) ({  })

/* * V2F - methods * */

static inline v2f	v2f_swap(v2f vec)				{ float v = vec[0]; vec[0] = vec[1]; vec[1] = v; return vec; }
static inline float	v2f_sum(v2f vec)				{ return vec[0] + vec[1]; }
static inline float	v2f_sub(v2f vec)				{ return vec[0] - vec[1]; }
static inline float	v2f_mul(v2f vec)				{ return vec[0] * vec[1]; }
static inline float	v2f_div(v2f vec)				{ return vec[0] / vec[1]; }
static inline float	v2f_mag(v2f vec)				{ return sqrtf(v2f_sum(vec * vec)); }
static inline v2f	v2f_norm(v2f vec)				{ return vec / v2f_mag(vec); }
static inline float	v2f_dot(v2f vec_a, v2f vec_b)	{ return v2f_sum(vec_a * vec_b); }
static inline float	v2f_cross(v2f vec_a, v2f vec_b)	{ return v2f_sub(vec_a * v2f_swap(vec_b)); }
// inline v2f		v2f_rot(v2f vec, float ang) {  }

/* actually does a 1 dimension rotation */
static inline v3f	v3f_swap_r(v3f vec)				{ return (v3f){vec[_y], vec[_z], vec[_x]}; }
static inline v3f	v3f_swap_l(v3f vec)				{ return (v3f){vec[_z], vec[_x], vec[_y]}; }

static inline float	v3f_sum(v3f vec)				{ return vec[0] + vec[1] + vec[2]; }
static inline float	v3f_sub(v3f vec)				{ return vec[0] - vec[1] - vec[2]; }
static inline float	v3f_mul(v3f vec)				{ return vec[0] * vec[1] * vec[2]; }
static inline float	v3f_div(v3f vec)				{ return vec[0] / vec[1] / vec[2]; }
static inline float	v3f_mag(v3f vec)				{ return sqrtf(v3f_sum(vec * vec)); }
static inline v3f	v3f_norm(v3f vec)				{ return vec / v3f_mag(vec); }
static inline float	v3f_dot(v3f vec_a, v3f vec_b)	{ return v3f_sum(vec_a * vec_b); }
static inline v3f	v3f_cross(v3f vec_a, v3f vec_b)	{ return v3f_swap_r(vec_a) * v3f_swap_l(vec_b) - v3f_swap_l(vec_a) * v3f_swap_r(vec_b); }

#endif
