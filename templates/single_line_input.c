#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
	int part1_sum = 0;
	int part2_sum = 0;
	char * line;
	while ( 1 == scanf("%ms", &line) ) {
		printf("line: %s\n", line);
	}
	printf("Part1: %d\n", part1_sum);
	printf("Part2: %d\n", part2_sum);
}
