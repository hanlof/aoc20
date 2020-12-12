#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

long long int numbers [2000];
int check(long long int val, int at)
{
	for (int i = at - 25; i < at; i++) {
		for (int j = at - 25; j < at; j++) {
			if (numbers[i] + numbers[j] == val)
				return 1;
		}
	}
	return 0;
}

long long int find_smallest_largest(int s, int e)
{
	long long int smallest = numbers[s];
	long long int biggest = numbers[s];
	for (int i = s; i <= e; i++) {
		if (numbers[i] < smallest) smallest = numbers[i];
		if (numbers[i] > biggest) biggest = numbers[i];
	}

	return biggest+ smallest;
}

int main(int argc, char * argv[])
{
	long long int part1_sum = 0;
	long long int part2_sum = 0;
	int i = 0;
	long long int t = 0;
	while ( 1 == scanf("%lld", &t) ) {
		numbers[i] = t;
		i++;
	}

	int ulimit = 0;
	for (int i = 25; i < 1000; i++) {
		if (!check(numbers[i], i)) {
			part1_sum = numbers[i];
			ulimit = i;
			break;
		}

	}
	long long int sum = 0;
	long long int start = 0;
	long long int end = ulimit;
	for (end = ulimit; end > 0; end--) {
		for (start = 0; start < end; start++) {
			sum = 0;
			for (int i = start; i < end; i++) {
				sum += numbers[i];
				if (sum > part1_sum) break;
				if (sum == part1_sum) {
					part2_sum = find_smallest_largest(start, i);
					goto done;
				}
			}
		}
	}
done:
	printf("Part1: %lld\n", part1_sum);
	printf("Part2: %lld\n", part2_sum);
}
