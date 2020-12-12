#ifndef __AOC_MAP_H
#define __AOC_MAP_H

int __global_map_width;
int __global_map_height;
int __global_map_size;
char * __global_map_data;
char * __original_map_data;
void readmap(char ** out_map, long int * out_width, long int * out_height)
{
	int tot_size = 1024;

	char * map = malloc(tot_size);
	char * cur_pos = &map[0];
	long int t;
	while ( (t = read(STDIN_FILENO, cur_pos, 1024)) > 0) {
		cur_pos += t;
		tot_size += 1024;
		map = realloc(map, tot_size);
	}
	__global_map_size = cur_pos - map;
	*out_map = malloc(__global_map_size);
	memcpy(*out_map, map, __global_map_size);
	__global_map_data = *out_map;
	__original_map_data = malloc(__global_map_size);

	memcpy(__original_map_data, map, __global_map_size);
	free(map);

	__global_map_width = strchr(*out_map, '\n') - *out_map;
	*out_width = __global_map_width;

	__global_map_height = __global_map_size / (*out_width + 1);
	*out_height = __global_map_height;
}

char * get_original_map()
{
	char * out_map = malloc(__global_map_size);
	memcpy(out_map, __original_map_data, __global_map_size);
	return out_map;
}

#define GLOBAL_MAP_POS(x, y) (__global_map_data[(y) * (__global_map_width + 1) + (x)])
#define MAP_POS(map, x, y) (map[(y) * (__global_map_width + 1) + (x)])

#endif // __AOC_MAP_H
