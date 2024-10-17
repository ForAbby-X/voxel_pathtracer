
#include "map.h"
#include "ray.h"

// int	ray_box_intersection(
// 			v3f const ray_pos,
// 			v3f const ray_dir,
// 			t_aabb const box,
// 			float *const t)
// {
// 	v3f const	dir_inv = 1.f / ray_dir;
// 	t_v2f		tmm;
// 	t_v2f		tg;
// 	int			d;

// 	tmm = (t_v2f){0.0f, INFINITY};
// 	d = 0;
// 	while (d < 3)
// 	{
// 		tg[0] = (box.pos[d] - ray_pos[d]) * dir_inv[d];
// 		tg[1] = (box.pos[d] + box.dim[d] - __FLT_EPSILON__ - ray_pos[d])
// 			* dir_inv[d];
// 		tmm[0] = fmax(tmm[0], fmin(fmin(tg[0], tg[1]), tmm[1]));
// 		tmm[1] = fmin(tmm[1], fmax(fmax(tg[0], tg[1]), tmm[0]));
// 		++d;
// 	}
// 	*t = tmm[0];
// 	return (tmm[0] < tmm[1] && tmm[1] >= 0.f && tmm[0] >= 0.f && tmm[0] < 1.f);
// }

__always_inline void ray_intersect(v3f ray_pos, v3f dir_inv, v3f box_min, v3f box_max, float *t)
{
	v3f off[2] = {(box_min - ray_pos) * dir_inv, (box_max - ray_pos) * dir_inv};
	float tm[2];

	enum {MIN, MAX};
	tm[MIN] = fminf(off[MIN][_x], off[MAX][_x]);
	tm[MAX] = fmaxf(off[MIN][_x], off[MAX][_x]);
	tm[MIN] = fmaxf(tm[MIN], fminf(off[MIN][_y], off[MAX][_y]));
	tm[MAX] = fminf(tm[MAX], fmaxf(off[MIN][_y], off[MAX][_y]));
	tm[MIN] = fmaxf(tm[MIN], fminf(off[MIN][_z], off[MAX][_z]));
	tm[MAX] = fminf(tm[MAX], fmaxf(off[MIN][_z], off[MAX][_z]));

	/* This is the percentage of direction at wich we intersect */	
	*t = tm[tm[0] < 0];
}

// __always_inline void __loop_ray(Map *const map, Ray ray, RayHit *const hit)
// {
// 	v3f start = ray.pos;

// 	v3ui block_pos = (v3ui){(int)(ray.pos[_x] + 1), (int)(ray.pos[_y] + 1), (int)(ray.pos[_z] + 1)} - 1;

// 	if (ray.dir[_x] == 0.0f) ray.dir[_x] = __FLT_EPSILON__ * 1e6f;
// 	if (ray.dir[_y] == 0.0f) ray.dir[_y] = __FLT_EPSILON__ * 1e6f;
// 	if (ray.dir[_z] == 0.0f) ray.dir[_z] = __FLT_EPSILON__ * 1e6f;

// 	v3f dir_inv = 1.0f / ray.dir;

// 	v3f dir_inv_abs;
// 	dir_inv_abs[_x] = fabsf(dir_inv[_x]);
// 	dir_inv_abs[_y] = fabsf(dir_inv[_y]);
// 	dir_inv_abs[_z] = fabsf(dir_inv[_z]);

// 	v3si ray_step = (ray.dir < 0) + ((ray.dir < 0) + 1); /* Unreadable but i am lazy */

// 	float t = 0.0f;

// 	hit->step = 0;

// 	// int last_move = 0;
// 	while (1)
// 	{
// 		if (block_pos[_x] >= map->size[_x]
// 		||  block_pos[_y] >= map->size[_y]
// 		||  block_pos[_z] >= map->size[_z])
// 			break ;

// 		v3ui chunk_pos = block_pos >> 3;
// 		v3ui b_pos = block_pos & 0b111;

// 		uint64_t idc = chunk_pos[_x] + chunk_pos[_y] * map->chunk_size[_x] + chunk_pos[_z] * map->chunk_size[_x] * map->chunk_size[_y];
// 		Chunk *chunk = &map->chunks[idc];

// 		if (chunk->blocks[b_pos[_x]][b_pos[_y]][b_pos[_z]])
// 			break ;

// 		if (chunk->occupency.mask)
// 		{
// 			/* DDA - Ray box positive intersection */

// 			v3f ray_side_dist;
// 			ray_side_dist[_x] = (ray.dir[_x] < 0) ? (ray.pos[_x] - block_pos[_x]) : (block_pos[_x] + 1.0f - ray.pos[_x]);
// 			ray_side_dist[_y] = (ray.dir[_y] < 0) ? (ray.pos[_y] - block_pos[_y]) : (block_pos[_y] + 1.0f - ray.pos[_y]);
// 			ray_side_dist[_z] = (ray.dir[_z] < 0) ? (ray.pos[_z] - block_pos[_z]) : (block_pos[_z] + 1.0f - ray.pos[_z]);
// 			ray_side_dist *= dir_inv_abs;

// 			v3si inc;
// 			while (chunk->blocks[b_pos[_x]][b_pos[_y]][b_pos[_z]] == 0)
// 			{
// 				inc[_x] = ((ray_side_dist[_x] <= ray_side_dist[_y]) && (ray_side_dist[_x] <= ray_side_dist[_z]));
// 				inc[_y] = ((ray_side_dist[_y] <= ray_side_dist[_x]) && (ray_side_dist[_y] <= ray_side_dist[_z]));
// 				inc[_z] = ((ray_side_dist[_z] <= ray_side_dist[_x]) && (ray_side_dist[_z] <= ray_side_dist[_y]));

// 				// /* Unreadable but slitghly faster on my cpu */
// 				// inc = (ray_side_dist > v3f_swap_r(ray_side_dist)) | (ray_side_dist > v3f_swap_l(ray_side_dist));
// 				// inc = inc + 1;
// 				// 	printf("inc %d %d %d\n", inc[_x], inc[_y], inc[_z]);

// 				if (inc[_x] == 0 && inc[_y] == 0 && inc[_z] == 0)
// 				{
// 					printf("ray_side_dist: x = %f, y = %f, z = %f\n", ray_side_dist[0], ray_side_dist[1], ray_side_dist[2]);
// 					printf("dir_inv_abs: x = %f, y = %f, z = %f\n", dir_inv_abs[0], dir_inv_abs[1], dir_inv_abs[2]);
// 					printf("inc: x = %d, y = %d, z = %d\n", inc[0], inc[1], inc[2]);
// 					printf("ray_step: x = %d, y = %d, z = %d\n", ray_step[0], ray_step[1], ray_step[2]);
// 				}

// 				b_pos += inc * ray_step;
// 				ray_side_dist += __builtin_convertvector(inc, v3f) * dir_inv_abs;
// 				hit->step++;

// 				if (inc[_x] == 0 && inc[_y] == 0 && inc[_z] == 0)
// 				{
// 					printf("	ray_side_dist: x = %f, y = %f, z = %f\n", ray_side_dist[0], ray_side_dist[1], ray_side_dist[2]);
// 					printf("	dir_inv_abs: x = %f, y = %f, z = %f\n", dir_inv_abs[0], dir_inv_abs[1], dir_inv_abs[2]);
// 					printf("	inc: x = %d, y = %d, z = %d\n", inc[0], inc[1], inc[2]);
// 					printf("	ray_step: x = %d, y = %d, z = %d\n", ray_step[0], ray_step[1], ray_step[2]);
// 					printf("	block_pos: x = %d, y = %d, z = %d\n", block_pos[0], block_pos[1], block_pos[2]);
// 					printf("	b_pos: x = %d, y = %d, z = %d\n", b_pos[0], b_pos[1], b_pos[2]);
// 					printf("	chunk_pos: x = %d, y = %d, z = %d\n", chunk_pos[0], chunk_pos[1], chunk_pos[2]);
// 					exit(0);
// 				}
// 				// if (ray_side_dist[_x] != ray_side_dist[_x] || ray_side_dist[_y] != ray_side_dist[_y] || ray_side_dist[_z] != ray_side_dist[_z])

// 				if (b_pos[_x] >= 8 || b_pos[_y] >= 8 || b_pos[_z] >= 8)
// 					break ;
// 			}

// 			block_pos = chunk_pos * 8 + b_pos;
			
// 			int side = inc[_y] | (inc[_z] << 1);
// 			float dist = ray_side_dist[side] - dir_inv_abs[side];
// 			ray.pos += dist * ray.dir;
// 		}
// 		else
// 		{
// 			/* Raw - Ray box intersection */

// 			v3f box_min = __builtin_convertvector(chunk_pos * 8, v3f) - 0.0001f;
// 			v3f box_max = box_min + 8.0f + 0.0001f * 2.0f;
			
// 			ray_intersect(ray.pos, dir_inv, box_min, box_max, &t);
// 			ray.pos += ray.dir * t;
// 			block_pos = (v3ui){(int)(ray.pos[_x] + 1), (int)(ray.pos[_y] + 1), (int)(ray.pos[_z] + 1)} - 1;
// 			hit->step++;
// 		}
// 	}
// 	hit->block_pos = block_pos;
// 	hit->normal = (v3f){0.0f, 0.0f, 0.0f};
// 	hit->real_pos = ray.pos;
// 	hit->dist = v3f_mag(ray.pos - start);
// }

RayHit map_cast_ray(Map *map, Ray ray)
{
	RayHit hit;

	v3f start = ray.pos;

	v3ui block_pos = (v3ui){(int)(ray.pos[_x] + 1), (int)(ray.pos[_y] + 1), (int)(ray.pos[_z] + 1)} - 1;

	if (ray.dir[_x] == 0.0f) ray.dir[_x] = __FLT_EPSILON__;
	if (ray.dir[_y] == 0.0f) ray.dir[_y] = __FLT_EPSILON__;
	if (ray.dir[_z] == 0.0f) ray.dir[_z] = __FLT_EPSILON__;

	v3f dir_inv = 1.0f / ray.dir;

	v3f dir_inv_abs;
	dir_inv_abs[_x] = fabsf(dir_inv[_x]);
	dir_inv_abs[_y] = fabsf(dir_inv[_y]);
	dir_inv_abs[_z] = fabsf(dir_inv[_z]);

	v3si ray_step = (ray.dir < 0) + ((ray.dir < 0) + 1); /* Unreadable but i am lazy */

	float t = 0.0f;

	hit.step = 0;

	while (1)
	{
		if (block_pos[_x] >= map->size[_x]
		||  block_pos[_y] >= map->size[_y]
		||  block_pos[_z] >= map->size[_z])
			break ;

		v3ui chunk_pos = block_pos >> 3;
		v3ui brick_pos = block_pos & 0b111;

		uint64_t idc = chunk_pos[_x] + chunk_pos[_y] * map->chunk_size[_x] + chunk_pos[_z] * map->chunk_size[_x] * map->chunk_size[_y];
		Chunk *chunk = &map->chunks[idc];

		if (chunk->blocks[brick_pos[_x]][brick_pos[_y]][brick_pos[_z]])
			break ;

		v3ui sub_brick_pos = brick_pos / 4;
		if (chunk->occupency.bricks[sub_brick_pos[_x]][sub_brick_pos[_y]][sub_brick_pos[_z]])
		{
			/* DDA - Ray box positive intersection */

			v3f ray_side_dist;
			ray_side_dist[_x] = (ray.dir[_x] < 0) ? (ray.pos[_x] - block_pos[_x]) : (block_pos[_x] + 1.0f - ray.pos[_x]);
			ray_side_dist[_y] = (ray.dir[_y] < 0) ? (ray.pos[_y] - block_pos[_y]) : (block_pos[_y] + 1.0f - ray.pos[_y]);
			ray_side_dist[_z] = (ray.dir[_z] < 0) ? (ray.pos[_z] - block_pos[_z]) : (block_pos[_z] + 1.0f - ray.pos[_z]);
			ray_side_dist *= dir_inv_abs;

			v3si inc;
			while (chunk->blocks[brick_pos[_x]][brick_pos[_y]][brick_pos[_z]] == 0)
			{
				inc[_x] = ((ray_side_dist[_x] <= ray_side_dist[_y]) && (ray_side_dist[_x] <= ray_side_dist[_z]));
				inc[_y] = ((ray_side_dist[_y] <= ray_side_dist[_x]) && (ray_side_dist[_y] <= ray_side_dist[_z]));
				inc[_z] = ((ray_side_dist[_z] <= ray_side_dist[_x]) && (ray_side_dist[_z] <= ray_side_dist[_y]));

				// /* Unreadable but slightly faster on my cpu ~10fps */
				// inc = (ray_side_dist > v3f_swap_r(ray_side_dist)) | (ray_side_dist > v3f_swap_l(ray_side_dist));
				// inc = inc + 1;

				brick_pos += inc * ray_step;
				ray_side_dist += __builtin_convertvector(inc, v3f) * dir_inv_abs;
				hit.step++;

				if (brick_pos[_x] >= 8 || brick_pos[_y] >= 8 || brick_pos[_z] >= 8)
					break ;
			}

			block_pos = chunk_pos * 8 + brick_pos;
			
			int side = inc[_y] | (inc[_z] << 1);
			float dist = ray_side_dist[side] - dir_inv_abs[side];
			ray.pos += dist * ray.dir;
		}
		else
		{
			/* Raw - Ray box intersection */

			v3f box_min;
			v3f box_max;

			if (chunk->occupency.mask == 0)
			{
			 	box_min = __builtin_convertvector(chunk_pos * 8, v3f) - 0.0001f;
				box_max = box_min + 8.0f + 0.0001f * 2.0f;
			}
			else
			{
			 	box_min = __builtin_convertvector(chunk_pos * 8 + sub_brick_pos * 4, v3f) - 0.0001f;
				box_max = box_min + 4.0f + 0.0001f * 2.0f;
			}

			ray_intersect(ray.pos, dir_inv, box_min, box_max, &t);
			ray.pos += ray.dir * t;
			block_pos = (v3ui){(int)(ray.pos[_x] + 1), (int)(ray.pos[_y] + 1), (int)(ray.pos[_z] + 1)} - 1;
			hit.step++;
		}
	}

	hit.block_pos = block_pos;
	hit.normal = (v3f){0.0f, 0.0f, 0.0f};
	hit.real_pos = ray.pos;
	hit.dist = v3f_mag(ray.pos - start);
	
	return (hit);
}

RayHit map_cast_ray_brick_depth(Map *map, Ray ray)
{
	RayHit hit;

	v3f start = ray.pos;

	v3ui block_pos = (v3ui){(int)(ray.pos[_x] + 1), (int)(ray.pos[_y] + 1), (int)(ray.pos[_z] + 1)} - 1;

	if (ray.dir[_x] == 0.0f) ray.dir[_x] = __FLT_EPSILON__;
	if (ray.dir[_y] == 0.0f) ray.dir[_y] = __FLT_EPSILON__;
	if (ray.dir[_z] == 0.0f) ray.dir[_z] = __FLT_EPSILON__;

	v3f dir_inv = 1.0f / ray.dir;

	float t = 0.0f;

	hit.step = 0;

	// int last_move = 0;
	while (1)
	{
		if (block_pos[_x] >= map->size[_x]
		||  block_pos[_y] >= map->size[_y]
		||  block_pos[_z] >= map->size[_z])
			break ;

		v3ui chunk_pos = block_pos >> 3;
		v3ui brick_pos = block_pos & 0b111;

		uint64_t idc = chunk_pos[_x] + chunk_pos[_y] * map->chunk_size[_x] + chunk_pos[_z] * map->chunk_size[_x] * map->chunk_size[_y];
		Chunk *chunk = &map->chunks[idc];

		if (chunk->blocks[brick_pos[_x]][brick_pos[_y]][brick_pos[_z]])
			break ;

		v3ui sub_brick_pos = brick_pos / 4;
		if (chunk->occupency.bricks[sub_brick_pos[_x]][sub_brick_pos[_y]][sub_brick_pos[_z]])
			break ;
		
		/* Raw - Ray box intersection */
		
		v3f box_min;
		v3f box_max;

		if (chunk->occupency.mask == 0)
		{
		 	box_min = __builtin_convertvector(chunk_pos * 8, v3f) - 0.0001f;
			box_max = box_min + 8.0f + 0.0001f * 2.0f;
		}
		else
		{
		 	box_min = __builtin_convertvector(chunk_pos * 8 + sub_brick_pos * 4, v3f) - 0.0001f;
			box_max = box_min + 4.0f + 0.0001f * 2.0f;
		}

		ray_intersect(ray.pos, dir_inv, box_min, box_max, &t);
		ray.pos += ray.dir * t;
		block_pos = (v3ui){(int)(ray.pos[_x] + 1), (int)(ray.pos[_y] + 1), (int)(ray.pos[_z] + 1)} - 1;
		hit.step++;
	}

	hit.block_pos = block_pos;
	hit.normal = (v3f){0.0f, 0.0f, 0.0f};
	hit.real_pos = ray.pos;
	hit.dist = v3f_mag(ray.pos - start);
	
	return (hit);
}
