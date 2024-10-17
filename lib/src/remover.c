/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remover.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:24:02 by alde-fre          #+#    #+#             */
/*   Updated: 2024/09/21 18:19:44 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_object	vector_pop(Vector *const vector)
{
	if (vector->size == 0)
		return (NULL);
	vector->copy_method(vector->buffer,
		vector->data + vector->type_size * (vector->size - 1),
		vector->type_size);
	vector->size--;
	return (vector->buffer);
}

t_object	vector_erase(Vector *const vector, t_length const index)
{
	if (vector->size == 0 || index >= vector->size)
		return (NULL);
	vector->copy_method(vector->buffer,
		vector->data + vector->type_size * index,
		vector->type_size);
	if (index + 1 < vector->size)
		_vec_memcpy(vector->data + vector->type_size * index,
			vector->data + vector->type_size * (index + 1),
			vector->type_size * (vector->size - index));
	vector->size--;
	return (vector->buffer);
}
