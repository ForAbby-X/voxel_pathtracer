
#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include "engine.h"
#include "math_vec/methodes.h"
#include "camera.h"
#include "ray.h"

#include "morton.h"

/* Chunks are 8 x 8 x 8 */
typedef struct Chunk
{
	union
	{
		uint64_t	mask;
		uint8_t		bricks[2][2][2];
	} occupency;
	uint8_t		blocks[8][8][8];
} Chunk;

typedef struct Map
{
	Chunk	*chunks;
	v3ui	chunk_size;
	v3ui	size;
} Map;

int		map_init(Map *map, v3ui chunk_size);
void	map_destroy(Map *map);

// void	map_generate_signed_distance_field(Map *map);

void	map_set(Map *map, v3ui pos, uint8_t value);

__always_inline uint8_t	map_get(Map *map, v3ui pos)
{
	if (pos[_x] >= map->size[_x]
	||  pos[_y] >= map->size[_y]
	||  pos[_z] >= map->size[_z])
		return 0xFF;

	v3ui chunk_pos = pos >> 3;
	v3ui block_pos = pos & 0b111;

	uint64_t idc = chunk_pos[_x] + chunk_pos[_y] * map->chunk_size[_x] + chunk_pos[_z] * map->chunk_size[_x] * map->chunk_size[_y];
	Chunk *chunk = &map->chunks[idc];

	return chunk->blocks[block_pos[_x]][block_pos[_y]][block_pos[_z]];
}

__always_inline uint8_t	map_occupency_get(Map *map, v3ui pos)
{
	if (pos[_x] >= map->size[_x]
	||  pos[_y] >= map->size[_y]
	||  pos[_z] >= map->size[_z])
		return 0;

	v3ui chunk_pos = pos >> 3;

	uint64_t idc = chunk_pos[_x] + chunk_pos[_y] * map->chunk_size[_x] + chunk_pos[_z] * map->chunk_size[_x] * map->chunk_size[_y];
	Chunk *chunk = &map->chunks[idc];

	// chunk->occupancy_mask; /* I should find a way to return this value */

	return chunk->occupency.mask;
}

RayHit	map_cast_ray(Map *map, Ray ray);
RayHit	map_cast_ray_brick_depth(Map *map, Ray ray);

void	map_render(Engine *eng, Map *map, Camera *cam);

#endif
