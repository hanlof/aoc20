#include <stdio.h>

#define GOAL (2020)
int input[200];
int main(int argc, char * argv[])
{
	for (int i = 0; i < 200; i++) {
		scanf("%d\n", &input[i]);
	}
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			if (j == i) continue;
			if (GOAL == (input[j] + input[i])) {
				printf("Part1: [%d * %d] = %d\n", input[j], input[i], input[j] * input[i]);
				goto part2;
			}
		}
	}
part2:
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			for (int k = 0; k < 200; k++) {
				if (GOAL == (input[k] + input[j] + input[i])) {
					printf("Part2: [%d * %d * %d] = %d\n", input[k], input[j], input[i], input[k] * input[j] * input[i]);
					goto done;
				}
			}
		}
	}
done: (void)GOAL;
}
