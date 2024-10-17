
#include "math_vec/methodes.h"
#include "random.h"
#include <stdio.h>
#include <time.h>

#include "engine.h"
#include "map.h"

#define TOK_ENUM(X) (#X)

struct s_data
{
	Sprite	*screen;
	Map		map;
	Camera	cam;
};

static int _init(Engine *eng, t_data *game)
{
	(void)eng;

	// my_srand_u32(time(NULL));
	my_srand_u32(0x42424242);

	game->screen = ft_sprite(eng, eng->screen->size[_x] / 2, eng->screen->size[_y] / 2);
	if (game->screen == NULL)
	{
		fprintf(stderr, "Error: sprite creation\n");
		return 1;
	}

	if (map_init(&game->map, (v3ui){64, 64, 64} / 8))
	{
		fprintf(stderr, "Error: map creation\n");
		return 1;
	}
	for (uint32_t x = 0; x < game->map.size[_x]; x++) {
		for (uint32_t y = 0; y < game->map.size[_y]; y++) {
			for (uint32_t z = 0; z < game->map.size[_z]; z++) {
				if (y > 58)
					map_set(&game->map, (v3si){x, y, z}, (my_rand_u32() & 63) < 1);
				else if (y < sinf(x / 64.0f * M_PI * 5) * 30.f)
					map_set(&game->map, (v3si){x, y, z}, 1);
			}
		}
	}

	// map_generate_signed_distance_field(&game->map);

	game->cam.fov = M_PI_2;
	game->cam.pos = (v3f){32.5f, 38.5f, 32.5f};
	game->cam.rot = (v2f){0.0f, 0.0f};

	return 0;
}

static int _on_repeat(Engine *eng, t_data *game, double dt)
{
	/* Handle controls */

	float sin_x = sinf(game->cam.rot[_x]);
	float cos_x = cosf(game->cam.rot[_x]);
	float sin_y = sinf(game->cam.rot[_y]);
	float cos_y = cosf(game->cam.rot[_y]);

	v3f dir = {sin_x * cos_y, -sin_y, cos_x * cos_y};
	v3f dir_right = {-cos_x, 0.0f, sin_x};

	if (ft_key(eng, XK_w).hold)
		game->cam.pos += dir * (float)dt * 2.0f;
	if (ft_key(eng, XK_s).hold)
		game->cam.pos -= dir * (float)dt * 2.0f;
	if (ft_key(eng, XK_a).hold)
		game->cam.pos += dir_right * (float)dt * 2.0f;
	if (ft_key(eng, XK_d).hold)
		game->cam.pos -= dir_right * (float)dt * 2.0f;

	if (ft_key(eng, XK_Left).hold)
		game->cam.rot[_x] -= dt * 2.0f;
	if (ft_key(eng, XK_Right).hold)
		game->cam.rot[_x] += dt * 2.0f;
	if (ft_key(eng, XK_Up).hold)
		game->cam.rot[_y] -= dt * 2.0f;
	if (ft_key(eng, XK_Down).hold)
		game->cam.rot[_y] += dt * 2.0f;

	/* Render */

	ft_eng_sel_spr(eng, game->screen);
	ft_clear(eng, (Color){0x00FF0000});
	map_render(eng, &game->map, &game->cam);

	ft_eng_sel_spr(eng, eng->screen);
	ft_put_sprite_s(eng, game->screen, (v2ui){0, 0}, 2);

	return 1;
}

int main()
{
	Engine *engine = ft_eng_create(1920 / 2, 1080 / 2, "Raytracer");
	t_data game;

	if (_init(engine, &game))
	{
		fprintf(stderr, "Error: initialisation failure.\n");
		return 1;
	}

	/* stops here to loop in engine */
	ft_eng_play(engine, &game, _on_repeat);

	map_destroy(&game.map);
	// ft_sprite_destroy(game.screen);
	ft_eng_destroy(engine);
	return 0;
}
