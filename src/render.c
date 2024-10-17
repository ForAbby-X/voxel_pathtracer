
#include "map.h"
#include "engine.h"
#include "pthread.h"
#include <time.h>

#define DEPTH_MAP_RESOLUTION 32

typedef struct Worker
{
	pthread_t thread;
	Engine *eng;
	Map *map;
	Camera *cam;
	v2ui pos;
	v2ui dim;
	float screen_dist;
	v3f plane_start;
	v3f plane_dir_right;
	v3f plane_dir_down;
	float *depth_mipmap;
} Worker;

void render_scop(Worker *worker)
{
	Engine *eng = worker->eng;
	Map *map = worker->map;
	Camera *cam = worker->cam;
	v2ui pos = worker->pos;
	v2ui dim = worker->dim;
	// float screen_dist = worker->screen_dist;
	v3f plane_left = worker->plane_start;
	v3f plane_dir_right = worker->plane_dir_right;
	v3f plane_dir_down = worker->plane_dir_down;
	
	for (uint32_t y = pos[_y]; y < pos[_y] + dim[_y]; ++y)
	{
		for (uint32_t x = pos[_x]; x < pos[_x] + dim[_x]; ++x)
		{
			Ray ray;
			ray.pos = cam->pos;
			v2f plane_ratio = {
				((float)x / (float)eng->sel_spr->size[_x]),
				((float)y / (float)eng->sel_spr->size[_y])};
			ray.dir = plane_left
				+ plane_dir_right * plane_ratio[_x] * 2.0f 
				+ plane_dir_down  * plane_ratio[_y] * 2.0f;

			v2ui depth_pos = __builtin_convertvector(plane_ratio * DEPTH_MAP_RESOLUTION, v2ui);
			ray.pos += v3f_norm(ray.dir) * worker->depth_mipmap[depth_pos[_x] + depth_pos[_y] * DEPTH_MAP_RESOLUTION];

			RayHit hit = map_cast_ray(map, ray);

			v3f text_coord = hit.real_pos - (v3f){hit.block_pos[_x], hit.block_pos[_y], hit.block_pos[_z]};
			
			// hit.dist += worker->depth_mipmap[depth_pos[_x] + depth_pos[_y] * DEPTH_MAP_RESOLUTION];
			// hit.dist /= 100.0f;
			// ft_draw(eng, (v2si){x, y}, ft_color_f(0.0f, hit.dist, hit.dist, hit.dist));
			// ft_draw(eng, (v2si){x, y}, ft_color(0, hit.step << 1, hit.step << 1, hit.step << 1));
			ft_draw(eng, (v2si){x, y}, ft_color_f(0, text_coord[_x], text_coord[_y], text_coord[_z]));
			// float depth = worker->depth_mipmap[depth_pos[_x] + depth_pos[_y] * DEPTH_MAP_RESOLUTION] / 100.0f;
			// ft_draw(eng, (v2si){x, y}, ft_color_f(0.0f, depth, depth, depth));
		}
	}
}

void render_depth_scop(Worker *worker)
{
	// Engine *eng = worker->eng;
	Map *map = worker->map;
	Camera *cam = worker->cam;
	v2ui pos = worker->pos;
	v2ui dim = worker->dim;
	v3f plane_left = worker->plane_start;
	v3f plane_dir_right = worker->plane_dir_right;
	v3f plane_dir_down = worker->plane_dir_down;
	
	for (uint32_t y = pos[_y]; y < pos[_y] + dim[_y]; ++y)
	{
		for (uint32_t x = pos[_x]; x < pos[_x] + dim[_x]; ++x)
		{
			Ray ray;
			ray.pos = cam->pos;
			v2f plane_ratio = {
				(((float)x + 0.5f) / (float)DEPTH_MAP_RESOLUTION * 2.0f),
				(((float)y + 0.5f) / (float)DEPTH_MAP_RESOLUTION * 2.0f)};
			ray.dir = plane_left
				+ plane_dir_right * plane_ratio[_x] 
				+ plane_dir_down * plane_ratio[_y];

			RayHit hit = map_cast_ray_brick_depth(map, ray);

			/* Here we save the depth of the pixel zone so that we can directly
			    jump to this depth when we launch a ray in this zone */
			worker->depth_mipmap[x + y * DEPTH_MAP_RESOLUTION] = hit.dist;
		}
	}
}


void map_render(Engine *eng, Map *map, Camera *cam)
{

	/* Screen planes setup */

	float sin_x = sinf(cam->rot[_x]);
	float cos_x = cosf(cam->rot[_x]);
	float sin_y = sinf(cam->rot[_y]);
	float cos_y = cosf(cam->rot[_y]);

	float fov_ratio = tanf(cam->fov / 2.f);
	float screen_dist = eng->sel_spr->size[_x] / 2.f / fov_ratio;

	v3f dir = {sin_x * cos_y, -sin_y, cos_x * cos_y};
	v3f plane_dir_right = (v3f){cos_x,0.0f, -sin_x}
							* ((float)eng->sel_spr->size[_x] / 2.0f);
	v3f plane_dir_down = (v3f){sin_x * -sin_y, -cos_y, cos_x * -sin_y}
							* ((float)eng->sel_spr->size[_y] / 2.0f);
	v3f plane_start = dir * screen_dist - plane_dir_right - plane_dir_down;


	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);


	/* Thread workers */

	int const num_worker = 8;
	Worker workers[num_worker];
	int per_worker;
	int rest;
	int total_worker;

	/* Pre render for brick depth */

	per_worker = DEPTH_MAP_RESOLUTION / num_worker;
	rest = DEPTH_MAP_RESOLUTION % num_worker;
	total_worker = 0;

	float depth_mipmap[DEPTH_MAP_RESOLUTION * DEPTH_MAP_RESOLUTION];

	for (uint32_t i = 0; i < num_worker; i++)
	{
		int this_worker = per_worker + (rest > 0 ? 1 : 0);
		workers[i].eng = eng;
		workers[i].map = map;
		workers[i].cam = cam;
		workers[i].pos = (v2ui){0, total_worker};
		workers[i].dim = (v2ui){DEPTH_MAP_RESOLUTION, this_worker};
		workers[i].plane_start = plane_start;
		workers[i].plane_dir_right = plane_dir_right;
		workers[i].plane_dir_down = plane_dir_down;
		workers[i].depth_mipmap = depth_mipmap;
		pthread_create(&workers[i].thread, NULL, (void *(*)(void *))render_depth_scop, &workers[i]);
		total_worker += per_worker + (rest > 0 ? 1 : 0);
	}

	for (uint32_t i = 0; i < num_worker; i++)
		pthread_join(workers[i].thread, NULL);

	/* Final render */

	per_worker = eng->sel_spr->size[_y] / num_worker;
	rest = eng->sel_spr->size[_y] % num_worker;
	total_worker = 0;
	for (uint32_t i = 0; i < num_worker; i++)
	{
		int this_worker = per_worker + (rest > 0 ? 1 : 0);
		workers[i].eng = eng;
		workers[i].map = map;
		workers[i].cam = cam;
		workers[i].pos = (v2ui){0, total_worker};
		workers[i].dim = (v2ui){eng->sel_spr->size[_x], this_worker};
		workers[i].screen_dist = screen_dist;
		workers[i].plane_start = plane_start;
		workers[i].plane_dir_right = plane_dir_right;
		workers[i].plane_dir_down = plane_dir_down;
		workers[i].depth_mipmap = depth_mipmap;
		pthread_create(&workers[i].thread, NULL, (void *(*)(void *))render_scop, &workers[i]);
		total_worker += per_worker + (rest > 0 ? 1 : 0);
	}

	for (uint32_t i = 0; i < num_worker; i++)
		pthread_join(workers[i].thread, NULL);


	clock_gettime(CLOCK_MONOTONIC, &end);
	double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

	static double tot_time = 0.0;
	static int nb_frame = 0;
	tot_time += elapsed_time;
	nb_frame++;

	double median_time = tot_time / (double)nb_frame;
	static double fps = 0.0;
	
	if (nb_frame > 10)
	{
		tot_time = 0.0;
		fps = 1.0 / median_time;
		nb_frame = 0;
	}

	printf("Frame render time: %f %d\n", elapsed_time, nb_frame);
	printf("Frame per secondes: %f\n", fps);
	// printf("Sizeof occupency: %lu\n", sizeof(map->chunks[0][0][0].occupency));
}