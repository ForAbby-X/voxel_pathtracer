/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:15:36 by alde-fre          #+#    #+#             */
/*   Updated: 2024/10/13 11:33:34 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# define MAX_KEYS 65535
# define MAX_MOUSE 5

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <time.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/extensions/Xfixes.h>
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include "vec2.h"
# include "vector.h"

typedef struct s_engine	Engine;
typedef struct s_key	t_key;
typedef union u_color	Color;
typedef struct s_sprite	Sprite;
typedef struct s_rect	t_rect;
typedef struct s_rect_s	t_rect_s;
/* USER ASSIGNED STRUCT */
typedef struct s_data	t_data;

/* ENGINE SETUP */
Engine	*ft_eng_create(size_t size_x, size_t size_y, char *title);
void		ft_eng_destroy(Engine *eng);
int			ft_eng_play(Engine *eng, t_data *data,
				int (*on_repeat)(Engine *, t_data *, double));

size_t		ft_eng_size_x(Engine *eng);
size_t		ft_eng_size_y(Engine *eng);
void		ft_eng_sel_spr(Engine *eng, Sprite	*spr);

t_key		ft_key(Engine *eng, int key_code);
t_key		ft_mouse(Engine *eng, int key_code);

/* ENGINE DRAWING */
/* [1] SHAPES */
void		ft_draw(Engine *eng, t_v2i pos, Color color);
void		ft_clear(Engine *eng, Color color);
void		ft_circle(Engine *eng, t_v2i pos, int r, Color color);
void		ft_rect(Engine *eng, t_v2i pos, t_v2i dim, Color color);

/* [2] SPRITE */
Color		ft_get_color(Sprite *spr, t_v2i pos);
void		ft_put_sprite(Engine *eng, Sprite *spr, t_v2i pos);
void		ft_put_sprite_s(Engine *eng, Sprite *spr, t_v2i pos, int d);
void		ft_get_border(Sprite *spr,
				t_v2i cen, float rot, t_v2i	out[2]);
void		ft_put_sprite_r(Engine *eng, Sprite *spr, t_rect i, float rot);

/* [3] SPRITE */
void		ft_put_sprite_part(Engine *eng, Sprite *spr,
				t_v2i pos, t_rect rect);
void		ft_put_sprite_part_s(Engine *eng, Sprite *spr,
				t_v2i pos, t_rect_s rect_t);
void		ft_put_text(Engine *eng, t_v2i pos, char *str, t_length size);
void		ft_put_nbr(Engine *eng, t_v2i pos, int nbr, t_length size);
void		ft_put_nbr_f(Engine *eng, t_v2i pos, float nbr, t_length size);

/* ENGINE EVENT */
/* [1] KEYS AND MOUSE */
int			ft_eng_pressed_keys(int keycode, Engine *eng);
int			ft_eng_pressed_mouse(int keycode, int x, int y, Engine *eng);
int			ft_eng_released_keys(int keycode, Engine *eng);
int			ft_eng_released_mouse(int keycode, int x, int y, Engine *eng);
int			ft_eng_moved_mouse(int x, int y, Engine *eng);
/* [2] CLOSING WINDOW*/
int			ft_eng_close(Engine *eng);
void		ft_hide_cursor(Engine *eng);
void		ft_show_cursor(Engine *eng);

/* COLOR */
Color		ft_color_d(uint32_t d);
Color		ft_color(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
Color		ft_color_f(float a, float r, float g, float b);
Color		ft_color_inter(Color col_a, Color col_b, float n);
uint8_t		ft_color_med(Color col);

/* SPRITE */
Sprite	*ft_sprite(Engine *eng, size_t dx, size_t dy);
Sprite	*ft_sprite_p(Engine *eng, char *path);
void		ft_engine_destroy_sprite(Engine *eng);
Sprite	*ft_cpy_sprite(Engine *eng, Sprite *spr);

/* UTILS */
int			ft_min(int a, int b);
int			ft_max(int a, int b);
void		ft_swap(void **a, void **b);
float		ft_rand(float min, float max);

void		_ft_itoa(int nb, char *tab);

struct	s_key
{
	char	pressed;
	char	hold;
	char	released;
};

struct	s_engine
{
	void			*mlx;
	void			*win;
	size_t			win_x;
	size_t			win_y;
	struct timespec	time_s;
	struct timespec	time_e;
	double			time_elapsed;
	Sprite		*screen;
	Sprite		*sel_spr;
	Sprite		*ascii_spr;
	char			keys[MAX_KEYS + 1];
	char			mouse[MAX_MOUSE + 1];
	char			old_keys[MAX_KEYS + 1];
	char			old_mouse[MAX_MOUSE + 1];
	int				mouse_x;
	int				mouse_y;
	int				(*on_repeat)(Engine *, t_data *, double);
	Vector		textures;
	t_data			*data;
};

union	u_color
{
	uint32_t	d;
	struct
	{
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
		uint8_t	a;
	};
};

struct	s_sprite
{
	t_img	img;
	Color	*data;
	t_v2i	size;
	char	*name;
};

struct s_rect
{
	t_v2i	pos;
	t_v2i	dim;
};

struct s_rect_s
{
	t_v2i	pos;
	t_v2i	dim;
	int		size;
};

#endif
