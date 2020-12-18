#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int input_lines = 0;
//int numbers[10000] = { 3,1,2, [ 3 ... 9999 ] = 0 };
int numbers[10000] = { 0, 14, 6, 20, 1, 4, [6 ... 9999] = 0 };
int find(int n, int start)
{
	for (int i = start; i >= 0; i--) {
		if (numbers[i] == n) return i;
	}
	return -1;
}

int main(int argc, char * argv[])
{
	long long int part1_sum = 0;
	long long int part2_sum = 0;

	int i = 6;
	int n = 0;
	do {
		int p = find(numbers[i - 1], i - 2);
		if (p >= 0) {
			n = i - 1 - p;
		} else {
			n = 0;
		}
		numbers[i] = n;
		i++;
	} while (i < 2020);

	for (int i = 0; i < 2020; i++) {
		printf("%d %d\n", i, numbers[i]);
	}
	part1_sum = numbers[i-1];
	printf("Part1: %lld\n", part1_sum);

	printf("Part2: %lld\n", part2_sum);
}
