/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 03:33:50 by alde-fre          #+#    #+#             */
/*   Updated: 2024/09/21 18:25:38 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	ft_eng_pressed_keys(int keycode, Engine *eng)
{
	if (keycode > MAX_KEYS)
		return (1);
	eng->keys[keycode] = 1;
	return (0);
}

int	ft_eng_pressed_mouse(int keycode, int x, int y, Engine *eng)
{
	(void)x;
	(void)y;
	eng->mouse[keycode] = 1;
	return (0);
}

int	ft_eng_released_keys(int keycode, Engine *eng)
{
	if (keycode > MAX_KEYS)
		return (1);
	eng->keys[keycode] = 0;
	return (0);
}

int	ft_eng_released_mouse(int keycode, int x, int y, Engine *eng)
{
	(void)x;
	(void)y;
	eng->mouse[keycode] = 0;
	return (0);
}

int	ft_eng_moved_mouse(int x, int y, Engine *eng)
{
	eng->mouse_x = x;
	eng->mouse_y = y;
	return (0);
}
