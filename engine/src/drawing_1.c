/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:15:32 by alde-fre          #+#    #+#             */
/*   Updated: 2024/09/21 18:25:38 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	ft_draw(Engine *eng, t_v2i pos, Color color)
{
	size_t	index;

	if ((color.d >> 24) == 255 || pos[0] < 0 || pos[1] < 0
		|| (size_t)pos[0] >= ft_eng_size_x(eng)
		|| (size_t)pos[1] >= ft_eng_size_y(eng))
		return ;
	index = pos[0] + pos[1] * ft_eng_size_x(eng);
	eng->sel_spr->data[index] = color;
}

void	ft_clear(Engine *eng, Color color)
{
	size_t	index;

	index = 0;
	while (index < ft_eng_size_x(eng) * ft_eng_size_y(eng))
	{
		eng->sel_spr->data[index] = color;
		index++;
	}
}

static void	ft_pt_circle(Engine *eng, t_v2i pos, t_v2i dim, Color color)
{
	ft_draw(eng, pos + dim, color);
	ft_draw(eng, (t_v2i){pos[0] - dim[0], pos[1] + dim[1]}, color);
	ft_draw(eng, (t_v2i){pos[0] + dim[0], pos[1] - dim[1]}, color);
	ft_draw(eng, pos - dim, color);
	ft_draw(eng, (t_v2i){pos[0] + dim[1], pos[1] + dim[0]}, color);
	ft_draw(eng, (t_v2i){pos[0] - dim[1], pos[1] + dim[0]}, color);
	ft_draw(eng, (t_v2i){pos[0] + dim[1], pos[1] - dim[0]}, color);
	ft_draw(eng, (t_v2i){pos[0] - dim[1], pos[1] - dim[0]}, color);
}

void	ft_circle(Engine *eng, t_v2i pos, int r, Color color)
{
	t_v2i	dim;
	int		d;

	dim[0] = 0;
	dim[1] = r;
	d = 3 - 2 * r;
	ft_pt_circle(eng, pos, dim, color);
	while (dim[1] >= dim[0])
	{
		dim[0]++;
		if (d > 0)
		{
			dim[1]--;
			d = d + 4 * (dim[0] - dim[1]) + 10;
		}
		else
			d = d + 4 * dim[0] + 6;
		ft_pt_circle(eng, pos, dim, color);
	}
}

void	ft_rect(Engine *eng, t_v2i pos, t_v2i dim, Color color)
{
	t_v2i	p;

	p[1] = 0;
	while (p[1] < dim[1])
	{
		p[0] = 0;
		while (p[0] < dim[0])
		{
			ft_draw(eng, pos + p, color);
			p[0]++;
		}
		p[1]++;
	}
}
