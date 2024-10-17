/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:16:34 by alde-fre          #+#    #+#             */
/*   Updated: 2024/09/21 18:19:44 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_length	vector_count_if(
				Vector const *const vector,
				int (*cond)(t_object object))
{
	t_length	index;
	t_length	count;

	index = 0;
	count = 0;
	while (index < vector->size)
	{
		if (cond(vector->data + vector->type_size * index) == 0)
			count++;
		index++;
	}
	return (count);
}

void	vector_for_each(
			Vector const *const vector,
			void (*func)(t_object object))
{
	t_length	index;

	index = 0;
	while (index < vector->size)
	{
		func(vector->data + vector->type_size * index);
		index++;
	}
}
