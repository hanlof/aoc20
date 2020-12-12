#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int input_lines = 0;
int main(int argc, char * argv[])
{
	long long int part1_sum = 0;
	long long int part2_sum = 0;
	char * line;
	while ( 1 == scanf("%ms", &line) ) {
		printf("line: %s\n", line);
		input_lines++;
	}
	printf("Part1: %lld\n", part1_sum);
	printf("Part2: %lld\n", part2_sum);
}
