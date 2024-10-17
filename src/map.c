
#include "map.h"
#include "morton.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

int map_init(Map *map, v3ui chunk_size)
{
	printf("Creating map with size of [%d, %d, %d]\n", chunk_size[_x], chunk_size[_y], chunk_size[_z]);

	map->size = chunk_size * 8; /* Chunks are 8 x 8 x 8*/
	map->chunk_size = chunk_size;
	map->chunks = malloc(chunk_size[_x] * chunk_size[_y] * chunk_size[_z] * sizeof(Chunk));
	if (map->chunks == NULL)
		return -1;
	memset(map->chunks, 0x00, chunk_size[_x] * chunk_size[_y] * chunk_size[_z] * sizeof(Chunk));
	return 0;
}

void map_destroy(Map *map)
{
	free(map->chunks);
}

// static uint8_t find_biggest_square_around_pos(Map *map, v3si pos)
// {
// 	uint8_t square_size = 1;

// 	while (square_size < 255)
// 	{
// 		for (int8_t z = -square_size; z <= square_size; z++)
// 		{
// 			for (int8_t y = -square_size; y <= square_size; y++)
// 			{
// 				for (int8_t x = -square_size; x <= square_size; x++)
// 				{
// 					if (x > -square_size && x < square_size
// 					 && y > -square_size && y < square_size
// 					 && z > -square_size && z < square_size)
// 						continue ;
// 					v3si _pos = pos + (v3si){x, y, z};
// 					if (map_get(map, _pos) == 1)
// 						return square_size;
// 				}
// 			}
// 		}
// 		square_size++;
// 	}
// 	return square_size;
// }

typedef struct Worker
{
	pthread_t	thread;
	Map			*map;
	v3ui		start;
	v3ui		dim;
} Worker;

// void worker_signed_dist(Worker *worker)
// {
// 	Map *map = worker->map;
// 	v3ui start = worker->start;
// 	v3ui dim = worker->dim;

// 	for (uint32_t z = start[_y]; z < start[_z] + dim[_z]; z++)
// 	{
// 		for (uint32_t y = start[_y]; y < start[_y] + dim[_y]; y++)
// 		{
// 			for (uint32_t x = start[_x]; x < start[_x] + dim[_x]; x++)
// 			{
// 				v3si pos = {x, y, z};
// 				// uint64_t idx = mortonEncode_LUT(x, y, z);
// 				uint64_t idx = x + y * map->size[_x] + z * map->size[_x] * map->size[_y];
// 				if (map->chunks[idx].value == 0)
// 					map->chunks[idx].dist = find_biggest_square_around_pos(map, pos);
// 			}
// 		}
// 	}
// }

// void map_generate_signed_distance_field(Map *map)
// {
// 	struct timespec start, end;
// 	clock_gettime(CLOCK_MONOTONIC, &start);

// 	int const nb_workers = 8;
// 	Worker workers[nb_workers];
// 	for (int i = 0; i < nb_workers; ++i)
// 	{
// 		workers[i].map = map;
// 		workers[i].start = (v3si){map->size[_x] / nb_workers * i, 0, 0};
// 		workers[i].dim =  (v3ui){map->size[_x] / nb_workers, map->size[_y], map->size[_z]};
// 		pthread_create(&workers[i].thread, NULL, (void *(*)(void *))worker_signed_dist, workers + i);
// 	}
// 	for (int i = 0; i < nb_workers; ++i)
// 		pthread_join(workers[i].thread, NULL);
	
// 	clock_gettime(CLOCK_MONOTONIC, &end);
// 	double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

// 	printf("Sdf calculation time: %f\n", elapsed_time);
// }

void map_set(Map *map, v3ui pos, uint8_t value)
{
	if (pos[_x] >= map->size[_x]
	||  pos[_y] >= map->size[_y]
	||  pos[_z] >= map->size[_z])
		return ;

	v3ui chunk_pos = pos >> 3;
	v3ui block_pos = pos & 0b111;

	uint64_t idc = chunk_pos[_x] + chunk_pos[_y] * map->chunk_size[_x] + chunk_pos[_z] * map->chunk_size[_x] * map->chunk_size[_y];
	Chunk *chunk = &map->chunks[idc];
	
	chunk->blocks[block_pos[_x]][block_pos[_y]][block_pos[_z]] = value;

	v3ui brick_pos = block_pos >> 2;
	chunk->occupency.bricks[brick_pos[_x]][brick_pos[_y]][brick_pos[_z]] |= value;
}

// __always_inline uint8_t map_get(Map *map, v3si pos)
// {
// 	v3ui _pos = pos; // shut your mouth compiler
// 	if (_pos[_x] < 0 || _pos[_x] >= map->size[_x]
// 	|| _pos[_y] < 0 || _pos[_y] >= map->size[_y]
// 	|| _pos[_z] < 0 || _pos[_z] >= map->size[_z])
// 		return 1;

// 	int idx = mortonEncode_LUT(_pos[_x], _pos[_y], _pos[_z]);
// 	return (map->data[idx >> 3] >> (idx & 7)) & 1;
// }
