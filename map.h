#ifndef __AOC_MAP_H
#define __AOC_MAP_H

int __global_map_width;
int __global_map_height;
char * __global_map_data;
void readmap(char ** out_map, long int * out_width, long int * out_height)
{
	int tot_size = 1024;

	char * map = malloc(tot_size);
	char * cur_pos = &map[0];
	long int tmp;
	while ( (tmp = read(STDIN_FILENO, cur_pos, 1024)) > 0) {
		cur_pos += tmp;
		tot_size += 1024;
		map = realloc(map, tot_size);
	}
	tmp = cur_pos - map;
	*out_map = malloc(tmp);
	__global_map_data = *out_map;
	memcpy(*out_map, map, tmp);
	free(map);

	__global_map_width = strchr(*out_map, '\n') - *out_map;
	*out_width = __global_map_width;

	__global_map_height = tmp / (*out_width + 1);
	*out_height = __global_map_height;
}

#define MAP_POS(x, y) (__global_map_data[y * (__global_map_width + 1) + x])

#endif // __AOC_MAP_H
