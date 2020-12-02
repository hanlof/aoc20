#include <stdio.h>

int main(int argc, char * argv[])
{
	int first_num, second_num;
	char ch;
	char * pwd;
	int part1_good = 0;
	int part1_bad = 0;
	int part2_good = 0;
	int part2_bad = 0;
	while (scanf("%d-%d %c: %ms\n", &first_num, &second_num, &ch, &pwd) == 4) {
		// Part1
		int count = 0;
		for (char * c = pwd; c[0]; c++) {
			if (c[0] == ch) count++;
		}
		if (count <= second_num && count >= first_num) {
			++part1_good;
		} else {
			++part1_bad;
		}
		// Part2
		first_num--; second_num--;
		if (pwd[first_num] == ch && pwd[second_num] == ch) {
			++part2_bad;
		} else if (pwd[first_num] == ch || pwd[second_num] == ch) {
			++part2_good;
		} else {
			++part2_bad;
		}
	}
	printf("Part1: %d\n", part1_good);
	printf("Part2: %d\n", part2_good);
}
