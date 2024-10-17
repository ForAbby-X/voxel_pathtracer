/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 03:33:54 by alde-fre          #+#    #+#             */
/*   Updated: 2024/09/21 18:25:38 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	ft_eng_close(Engine *eng)
{
	mlx_loop_end(eng->mlx);
	return (0);
}

void	ft_hide_cursor(Engine *eng)
{
	XFixesHideCursor(((t_xvar *)eng->mlx)->display,
		((t_win_list *)eng->win)->window);
}

void	ft_show_cursor(Engine *eng)
{
	XFixesShowCursor(((t_xvar *)eng->mlx)->display,
		((t_win_list *)eng->win)->window);
}
