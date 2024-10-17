/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:48:37 by alde-fre          #+#    #+#             */
/*   Updated: 2024/09/21 18:33:24 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline Sprite	*__is_sprite_present(
						Engine const *const eng,
						char const *const path)
{
	Sprite	*spr;
	t_length	index;

	index = 0;
	while (index < vector_size(&eng->textures))
	{
		spr = vector_get(&eng->textures, index);
		if (spr->name && ft_strncmp(spr->name, path, 999999) == 0)
		{
			ft_putstr_fd("Found sprite #", 1);
			ft_putnbr_fd(index, 1);
			ft_putstr_fd(" [", 1);
			ft_putstr_fd(spr->name, 1);
			ft_putstr_fd("]\n", 1);
			return (spr);
		}
		++index;
	}
	return (NULL);
}

Sprite	*ft_sprite(Engine *eng, size_t dx, size_t dy)
{
	Sprite	spr;
	Sprite	*ret;
	int			tab[3];

	spr.img.image = mlx_new_image(eng->mlx, dx, dy);
	if (spr.img.image == NULL)
		return (NULL);
	spr.img.data
		= mlx_get_data_addr(spr.img.image, &tab[0], &tab[1], &tab[2]);
	spr.data = (Color *)(uint32_t *)spr.img.data;
	spr.size = (t_v2i){dx, dy};
	ft_memset(spr.data, 0x00, sizeof(Color) * spr.size[0] * spr.size[1]);
	spr.name = NULL;
	ret = vector_addback(&eng->textures, &spr);
	if (ret == NULL)
		return (mlx_destroy_image(eng->mlx, spr.img.image), NULL);
	ft_putstr_fd("Added sprite #", 1);
	ft_putnbr_fd(eng->textures.size - 1, 1);
	ft_putstr_fd(" [", 1);
	ft_putnbr_fd(spr.size[0], 1);
	ft_putstr_fd(":", 1);
	ft_putnbr_fd(spr.size[1], 1);
	ft_putstr_fd("]\n", 1);
	return (ret);
}

Sprite	*ft_sprite_p(Engine *eng, char *path)
{
	Sprite	spr;
	Sprite	*ret;
	int			tab[3];
	int			xy[2];

	if (__is_sprite_present(eng, path))
		return (__is_sprite_present(eng, path));
	spr.name = ft_strdup(path);
	if (spr.name == NULL)
		return (NULL);
	spr.img.image = mlx_xpm_file_to_image(eng->mlx, path, &xy[0], &xy[1]);
	if (spr.img.image == NULL)
		return (free(spr.name), NULL);
	spr.size = (t_v2i){xy[0], xy[1]};
	spr.img.data
		= mlx_get_data_addr(spr.img.image, &tab[0], &tab[1], &tab[2]);
	spr.data = (Color *)(uint32_t *)spr.img.data;
	ret = vector_addback(&eng->textures, &spr);
	if (ret == NULL)
		return (free(spr.name), mlx_destroy_image(eng->mlx, spr.img.image),
			NULL);
	ft_putstr_fd("Added sprite #", 1);
	ft_putnbr_fd(eng->textures.size - 1, 1);
	ft_putstr_fd(" - [", 1);
	return (ft_putstr_fd(path, 1), ft_putstr_fd("]\n", 1), ret);
}

void	ft_engine_destroy_sprite(Engine *eng)
{
	Sprite	*spr;
	t_length	index;

	index = 0;
	while (index < vector_size(&eng->textures))
	{
		spr = vector_get(&eng->textures, index);
		mlx_destroy_image(eng->mlx, spr->img.image);
		free(spr->name);
		++index;
	}
	ft_putstr_fd("Destroyed [", 1);
	ft_putnbr_fd(index, 1);
	ft_putstr_fd("] sprites !\n", 1);
}

Sprite	*ft_cpy_sprite(Engine *eng, Sprite *spr)
{
	Sprite	*res;

	if (spr == NULL)
		return (NULL);
	res = ft_sprite(eng, spr->size[0], spr->size[1]);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res->data,
		spr->data, spr->size[0] * spr->size[1] * sizeof(Color));
	spr->name = NULL;
	return (res);
}
