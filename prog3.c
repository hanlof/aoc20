#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "map.h"

long int map_width, map_height;

int countslope(char * map, int sx, int sy)
{
	int trees = 0;
	int tx = 0;
	int ty = 0;
	while (ty < map_height) {
		if (MAP_POS(tx, ty) == '#') trees++;
		ty += sy;
		tx += sx;
		if (tx >= map_width) tx -= map_width;
	}
	return trees;
}

int main(int argc, char * argv[])
{
	char * map;
	readmap(&map, &map_width, &map_height);

	long int tmp = countslope(map, 3, 1);
	printf("Part1: %ld\n", tmp);

	tmp = 1;
	tmp *= countslope(map, 1, 1);
	tmp *= countslope(map, 3, 1);
	tmp *= countslope(map, 5, 1);
	tmp *= countslope(map, 7, 1);
	tmp *= countslope(map, 1, 2);
	printf("Part2: %ld\n", tmp);

}
