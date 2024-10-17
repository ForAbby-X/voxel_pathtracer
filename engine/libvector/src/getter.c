/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:43:22 by alde-fre          #+#    #+#             */
/*   Updated: 2024/09/21 18:19:44 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_object	vector_get(Vector const *const vector, t_length const index)
{
	if (index >= vector->size)
		return (NULL);
	return (vector->data + index * vector->type_size);
}

t_object	vector_buffer(Vector const *const vector)
{
	return (vector->buffer);
}

t_length	vector_size(Vector const *const vector)
{
	return (vector->size);
}

t_length	vector_capacity(Vector const *const vector)
{
	return (vector->capacity);
}

Vector	vector_subvec(
				Vector const *const vector,
				t_length const index,
				t_length const length)
{
	Vector	sub;

	sub = vector_create(vector->type_size);
	if (sub.data == NULL)
		return ((Vector){0});
	if (vector_resize(&sub, length))
	{
		vector_destroy(&sub);
		return ((Vector){0});
	}
	if (index + length <= vector->size)
		_vec_memcpy(sub.data,
			vector->data + vector->type_size * index,
			vector->type_size * length);
	else
		_vec_memcpy(sub.data,
			vector->data + vector->type_size * index,
			vector->type_size * (vector->size - index + length));
	return (sub);
}
