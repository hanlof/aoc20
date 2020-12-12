#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "map.h"

long int map_width, map_height;

int within_map(int x, int y)
{
	if (x < 0 || x >= map_width) return 0;
	if (y < 0 || y >= map_height) return 0;
	return 1;

}

int count_adjacent(char * map, int x, int y)
{
	int count = 0;
	if (within_map(x-1,y-1)) {
		if (MAP_POS(map, x-1, y-1) == '#') count++;
	}
	if (within_map(x  ,y-1)) {
		if (MAP_POS(map, x, y-1) == '#') count++;
	}
	if (within_map(x+1,y-1)) {
		if (MAP_POS(map, x+1, y-1) == '#') count++;
	}
	if (within_map(x-1,y+1)) {
		if (MAP_POS(map, x-1, y+1) == '#') count++;
	}
	if (within_map(x  ,y+1)) {
		if (MAP_POS(map, x, y+1) == '#') count++;
	}
	if (within_map(x+1,y+1)) {
		if (MAP_POS(map, x+1, y+1) == '#') count++;
	}
	if (within_map(x-1,y)) {
		if (MAP_POS(map, x-1, y) == '#') count++;
	}
	if (within_map(x+1,y)) {
		if (MAP_POS(map, x+1, y) == '#') count++;
	}
	return count;
}

void apply_rules_1(char * from, char * to)
{
	for (int i = 0; i < map_width; i++) {
		for (int j = 0; j < map_height; j++) {
			MAP_POS(to, i, j) = MAP_POS(from, i, j);
			if (MAP_POS(from, i, j) == '.') continue;
			int t = count_adjacent(from, i, j);
			if (t == 0 && MAP_POS(from, i, j) == 'L') {
				MAP_POS(to, i, j) = '#';
			}
			if (t >= 4 && MAP_POS(from, i, j) == '#') {
				MAP_POS(to, i, j) = 'L';
			}
		}
	}

}

int check_direction(char * map, int x, int y, int dx, int dy)
{
	x += dx;
	y += dy;
	for ( ; within_map(x, y); x += dx, y += dy) {
		if (MAP_POS(map, x, y) == '.') continue;
		if (MAP_POS(map, x, y) == '#') return 1;
		if (MAP_POS(map, x, y) == 'L') break;
		x += dx;
		y += dy;
	}
	return 0;
}

void apply_rules_2(char * from, char * to)
{
	for (int i = 0; i < map_width; i++) {
		for (int j = 0; j < map_height; j++) {
			MAP_POS(to, i, j) = MAP_POS(from, i, j);
			if (MAP_POS(from, i, j) == '.') continue;
			int count = 0;
			count += check_direction(from, i, j, -1, -1);
			count += check_direction(from, i, j, -1,  0);
			count += check_direction(from, i, j, -1,  1);
			count += check_direction(from, i, j,  0, -1);
			count += check_direction(from, i, j,  0,  1);
			count += check_direction(from, i, j,  1, -1);
			count += check_direction(from, i, j,  1,  0);
			count += check_direction(from, i, j,  1,  1);
			if (count == 0 && MAP_POS(from, i, j) == 'L') {
				MAP_POS(to, i, j) = '#';
			}
			if (count >= 5 && MAP_POS(from, i, j) == '#') {
				MAP_POS(to, i, j) = 'L';
			}
		}
	}

}
int main(int argc, char * argv[])
{
	char * map;
	readmap(&map, &map_width, &map_height);
	char * map2 = malloc(strlen(map)*2);
	strcpy(map2, map);

	char * from_map = map;
	char * to_map = map2;
	int cont = 1;
	while (cont) {
		apply_rules_1(from_map, to_map);
		if (to_map == map) {
			to_map = map2;
			from_map = map;
		} else {
			to_map = map;
			from_map = map2;
		}
		cont = strcmp(from_map, to_map);
	}
	int part1_sum = 0;
	for (int i = 0; i < map_width; i++) {
		for (int j = 0; j < map_height; j++) {
			if (MAP_POS(from_map, i, j) == '#') part1_sum++;
		}
	}
	printf("Part1: %d\n", part1_sum);

	map = get_original_map();
	map2 = get_original_map();
	from_map = map;
	to_map = map2;
	cont = 1;
	while (cont) {
		apply_rules_2(from_map, to_map);
		if (to_map == map) {
			to_map = map2;
			from_map = map;
		} else {
			to_map = map;
			from_map = map2;
		}
		cont = strcmp(from_map, to_map);
	}
	int part2_sum = 0;
	for (int i = 0; i < map_width; i++) {
		for (int j = 0; j < map_height; j++) {
			if (MAP_POS(from_map, i, j) == '#') part2_sum++;
		}
	}
	printf("Part2: %d\n", part2_sum);
}
