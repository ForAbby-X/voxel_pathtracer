/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 09:10:59 by alde-fre          #+#    #+#             */
/*   Updated: 2024/09/21 18:25:03 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

Color	ft_color_d(uint32_t d)
{
	Color	col;

	col.d = d;
	return (col);
}

Color	ft_color(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
	Color	col;

	col.a = a;
	col.r = r;
	col.g = g;
	col.b = b;
	return (col);
}

Color	ft_color_f(float a, float r, float g, float b)
{
	Color	col;

	col.a = a * 255;
	col.r = r * 255;
	col.g = g * 255;
	col.b = b * 255;
	return (col);
}

Color	ft_color_inter(Color col_a, Color col_b, float n)
{
	Color	col;

	if (n < 0.0f)
		return (col_b);
	if (n > 1.0f)
		return (col_a);
	col.a = 0;
	col.r = col_a.r * n + col_b.r * (1.0f - n);
	col.g = col_a.g * n + col_b.g * (1.0f - n);
	col.b = col_a.b * n + col_b.b * (1.0f - n);
	return (col);
}

uint8_t	ft_color_med(Color col)
{
	uint8_t	med;

	med = (col.r + col.g + col.b) / 3;
	return (med);
}
