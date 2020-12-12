#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "map.h"

long int map_width, map_height;

int main(int argc, char * argv[])
{
	char * map;
	readmap(&map, &map_width, &map_height);

	printf("map size: %ld %ld\n", map_width, map_height);
}
