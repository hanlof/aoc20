#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main(int argc, char * argv[])
{
	long long int part1_sum = 0;
	long long int part2_sum = 0;
	char * line;
	while (!feof(stdin)) {
		// When this loop condition is not met we started parsing on an
		// empty line (the first character we hit is NOT NOT '\n')
		int group_members = 0;
		while (scanf("%m[^\n]", &line) > 0) {
			// When the body of this look is entered we have one
			// valid line from the input in tmp.

			printf("%s\n", line);
			(void) getchar(); // eat up the endline
		}
		printf("--- group delimeter ---\n");
		(void) getchar(); // eat up the second endline (on empty lines)
	}
	printf("Part1: %lld\n", part1_sum);
	printf("Part2: %lld\n", part2_sum);
}
