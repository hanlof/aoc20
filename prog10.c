#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int numbers[200];
int clusters[200] = { [0 ... 199] = 0 };
int main(int argc, char * argv[])
{
	int part1_sum = 0;
	long long int part2_sum = 0;
	int num;
	int elements = 0;
	while ( 1 == scanf("%d", &num) ) {
		numbers[elements] = num;
		elements++;
	}
	int _1diff = 0;
	int _3diff = 0;

	// using pre-sorted list (modified input) so no need to sort it! XXX
	int cluster_size = 1;
	int cluster_count = 0;
	if (numbers[0] == 1) cluster_size++;
	for (int i = 1; i < elements; i++) {
		int diff = numbers[i] - numbers[i - 1];
		if (diff == 1) {
			_1diff++;
			cluster_size++;
		} else if (diff == 3) {
			_3diff++;
			if (cluster_size > 1) {
				clusters[cluster_count] = cluster_size;
				cluster_count++;
			}
			cluster_size = 1;
		}
	}

	_1diff++; // because of the jump from 0 to the first number
	_3diff++; // because "my device" is always 3 higher than last number
	part1_sum = _1diff * _3diff;
	printf("Part1: %d\n", part1_sum);


	part2_sum = 1;
	for (int i = 0; i < cluster_count; i++) {
		if (clusters[i] == 3) {
			part2_sum *= 2;
		} else if (clusters[i] == 4) {
			part2_sum *= 4;
		} else if (clusters[i] == 5) {
			part2_sum *= 7;
		} else {
			printf("cluster: %d\n", clusters[i]);
		}
		printf("sum: (%d) %lld\n", clusters[i], part2_sum);
	}
	printf("Part2: %lld\n", part2_sum);
	// O  O  O - 2 ways
	// using only ones: exactly 1 way!
	// using only twos: exactly 1 way!
	//
	// O  O  O  O - 4 ways
	// using only ones: exactly 1 way
	// using only threes: exactly 1 way
	// using only twos: 0 ways
	// using twos and ones: 2 ways!
	//
	// O  O  O  O  O - 7 ways
	// using only ones: exactly 1 way
	// using threes (and ones): exactly 2 ways
	// using only twos: exactly 1 ways
	// using twos and ones: 3 ways
	// 1 2 1
	// 1 1 2
	// 2 1 1
}
