
/* Defines basic types for 2d vector storage and operations */

#ifndef MATH_VEC_TYPES_H
#define MATH_VEC_TYPES_H

/* vector 2d */

typedef char				v2sc __attribute__((vector_size(2)));
typedef unsigned char		v2uc __attribute__((vector_size(2)));
typedef int					v2si __attribute__((vector_size(8)));
typedef unsigned int		v2ui __attribute__((vector_size(8)));
typedef short int			v2ssi __attribute__((vector_size(4)));
typedef unsigned short int	v2sui __attribute__((vector_size(4)));
typedef long				v2sl __attribute__((vector_size(8)));
typedef unsigned long		v2ul __attribute__((vector_size(8)));
typedef float				v2f __attribute__((vector_size(8)));
typedef double				v2d __attribute__((vector_size(16)));

typedef v2sc				vec2_schar;
typedef v2uc				vec2_uchar;
typedef v2si				vec2_sint;
typedef v2uc				vec2_uint;
typedef v2ssi				vec2_ssint;
typedef v2sui				vec2_suint;
typedef v2sl				vec2_slong;
typedef v2ul				vec2_ulong;
typedef v2f					vec2_float;
typedef v2d					vec2_double;


/* vector 4d */

typedef char				v4sc __attribute__((vector_size(4)));
typedef unsigned char		v4uc __attribute__((vector_size(4)));
typedef int					v4si __attribute__((vector_size(16)));
typedef unsigned int		v4ui __attribute__((vector_size(16)));
typedef short int			v4ssi __attribute__((vector_size(8)));
typedef unsigned short int	v4sui __attribute__((vector_size(8)));
typedef long				v4sl __attribute__((vector_size(16)));
typedef unsigned long		v4ul __attribute__((vector_size(16)));
typedef float				v4f __attribute__((vector_size(16)));
typedef double				v4d __attribute__((vector_size(32)));

typedef v4sc				vec4_schar;
typedef v4uc				vec4_uchar;
typedef v4si				vec4_sint;
typedef v4ui				vec4_uint;
typedef v4ssi				vec4_ssint;
typedef v4sui				vec4_suint;
typedef v4sl				vec4_slong;
typedef v4ul				vec4_ulong;
typedef v4f					vec4_float;
typedef v4d					vec4_double;

typedef v4sc				v3sc;
typedef v4uc				v3uc;
typedef v4si				v3si;
typedef v4ui				v3ui;
typedef v4ssi				v3ssi;
typedef v4sui				v3sui;
typedef v4sl				v3sl;
typedef v4ul				v3ul;
typedef v4f					v3f;
typedef v4d					v3d;

/* rectangle */

typedef struct				r2sc { v2sc pos; v2sc dim; }	r2sc;
typedef struct				r2uc { v2uc pos; v2uc dim; }	r2uc;
typedef struct				r2si { v2si pos; v2si dim; }	r2si;
typedef struct				r2ui { v2ui pos; v2ui dim; }	r2ui;
typedef struct				r2ssi { v2ssi pos; v2ssi dim; }	r2ssi;
typedef struct				r2sui { v2sui pos; v2sui dim; }	r2sui;
typedef struct				r2sl { v2sl pos; v2sl dim; }	r2sl;
typedef struct				r2ul { v2ul pos; v2ul dim; }	r2ul;
typedef struct				r2f { v2f pos; v2f dim; }		r2f;
typedef struct				r2d { v2d pos; v2d dim; }		r2d;

typedef r2sc				rect2_schar;
typedef r2sc				rect2_uchar;
typedef r2si				rect2_sint;
typedef r2uc				rect2_uint;
typedef r2ssi				rect2_ssint;
typedef r2sui				rect2_suint;
typedef r2sl				rect2_slong;
typedef r2ul				rect2_ulong;
typedef r2f					rect2_float;
typedef r2d					rect2_double;

enum
{
	_x = 0,
	_y = 1,
	_z = 2,
	_w = 3,
};

#endif
