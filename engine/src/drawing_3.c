/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:41:05 by alde-fre          #+#    #+#             */
/*   Updated: 2024/09/21 18:33:24 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	ft_put_sprite_part(Engine *eng, Sprite *spr, t_v2i pos, t_rect rect)
{
	t_v2i	dim;

	dim[1] = 0;
	while (dim[1] < rect.dim[1])
	{
		dim[0] = 0;
		while (dim[0] < rect.dim[0])
		{
			ft_draw(eng, pos + dim, ft_get_color(spr, rect.pos + dim));
			dim[0]++;
		}
		dim[1]++;
	}
}

void	ft_put_sprite_part_s(Engine *eng, Sprite *spr,
		t_v2i pos, t_rect_s rect_t)
{
	t_v2i	dim;

	dim[1] = 0;
	while (dim[1] < rect_t.dim[1])
	{
		dim[0] = 0;
		while (dim[0] < rect_t.dim[0])
		{
			ft_rect(eng, pos + dim * rect_t.size,
				(t_v2i){rect_t.size, rect_t.size},
				ft_get_color(spr, rect_t.pos + dim));
			dim[0]++;
		}
		dim[1]++;
	}
}

void	ft_put_text(Engine *eng, t_v2i pos, char *str, t_length size)
{
	t_length	i;
	char		c;

	i = 0;
	while (str[i])
	{
		c = str[i] - '!';
		if (c < -1 || c > 96)
			c = 3;
		if (c >= 0)
			ft_put_sprite_part_s(eng, eng->ascii_spr,
				(t_v2i){pos[0] + i * 7 * size + size, pos[1] + size},
				(t_rect_s){
				(t_v2i){c * 5, 0},
				(t_v2i){5, 7}, size});
		i++;
	}
}

void	ft_put_nbr(Engine *eng, t_v2i pos, int nbr, t_length size)
{
	char	tab[12];

	_ft_itoa(nbr, tab);
	ft_put_text(eng, pos, tab, size);
}

void	ft_put_nbr_f(Engine *eng, t_v2i pos, float nbr, t_length size)
{
	char	tab[12];
	size_t	len;

	if (nbr < 0.0f && nbr > -1.0f)
	{
		ft_put_text(eng, pos, "-0", size);
		len = 2;
	}
	else
	{
		_ft_itoa(nbr, tab);
		ft_put_text(eng, pos, tab, size);
		len = ft_strlen(tab);
	}
	if (nbr < 0.0f)
		nbr = -nbr;
	_ft_itoa((nbr - (int)nbr) * 1000, tab);
	ft_put_text(eng, pos + (t_v2i){len * 7 * size, 0}, ",", size);
	ft_put_text(eng, pos + (t_v2i){(len + 1) * 7 * size, 0}, tab, size);
}
