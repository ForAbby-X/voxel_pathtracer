/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:17:22 by alde-fre          #+#    #+#             */
/*   Updated: 2024/09/21 18:21:12 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

# ifndef VECTOR_DEFAULT_SIZE
#  define VECTOR_DEFAULT_SIZE 64
# endif

//-Storage class for any types
typedef struct s_vector	Vector;
//-Type for storing vector error
typedef enum e_error	t_error;
//-Type for storing vector length
typedef unsigned int	t_length;
typedef void			*t_object;
typedef t_object		(*t_copy_method)(
			void *dest, void *src, t_length const len);

void		*_vec_memcpy(void *dest, void *src, t_length const len);
void		_vec_memmov(void *dest, void *src, t_length len);

Vector	vector_create(t_length const type_size);
void		vector_destroy(Vector *const vector);
void		vector_set_copy_method(Vector *const vector, t_copy_method cpy_m);
//BOTH VECTORS MUST BE INITIALISED BEFORE
Vector	*vector_copy(Vector *const vec_dest, Vector *const vec_src);

t_error		vector_reserve(Vector *const vector, t_length const len);
t_error		vector_resize(Vector *const vector, t_length const len);
void		vector_clear(Vector *const vector);
t_error		vector_shrink_to_fit(Vector *const vector);

t_object	vector_addback(Vector *const vector, t_object object);
t_object	vector_addfront(Vector *const vector, t_object object);
t_object	vector_insert(
				Vector *const vector,
				t_object object,
				t_length const index);
Vector	*vector_insert_vector(
				Vector *const vec_dest,
				Vector const *const vec_src,
				t_length const index);

t_object	vector_pop(Vector *const vector);
t_object	vector_erase(Vector *const vector, t_length const index);

t_object	vector_get(Vector const *const vector, t_length const index);
t_object	vector_buffer(Vector const *const vector);
t_length	vector_size(Vector const *const vector);
t_length	vector_capacity(Vector const *const vector);
Vector	vector_subvec(
				Vector const *const vector,
				t_length const index,
				t_length const length);

t_length	vector_count_if(
				Vector const *const vector,
				int (*cond)(t_object object));
void		vector_for_each(
				Vector const *const vector,
				void (*func)(t_object object));

void		_vec_choose_method(Vector *const vector);

t_object	_1byte_copy_method(void *dest, void *src, t_length const len);
t_object	_2byte_copy_method(void *dest, void *src, t_length const len);
t_object	_4byte_copy_method(void *dest, void *src, t_length const len);
t_object	_8byte_copy_method(void *dest, void *src, t_length const len);

enum e_error
{
	VEC_SUCCES = 0,
	VEC_FAILURE = 1,
	VEC_MEMORY_FAILURE = 2,
	VEC_OBJECT_TYPE_MISMATCH = 3
};

struct s_vector
{
	void			*data;
	t_length		size;
	t_length		capacity;
	void			*buffer;
	t_length		type_size;
	t_copy_method	copy_method;
};

#endif
