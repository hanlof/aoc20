#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int input_lines = 0;

char instr[1024];
int i_num[1024];

void rot_r(int * x, int * y, int steps) {
	while (steps--) {
		int t = *x;
		*x = *y;
		*y = -t;
	}
}

void rot_l(int * x, int * y, int steps) {
	while (steps--) {
		int t = *x;
		*x = -*y;
		*y = t;
	}
}
int main(int argc, char * argv[])
{
	long long int part1_sum = 0;
	long long int part2_sum = 0;

	while ( 2 == scanf("%c%d\n", &instr[input_lines], &i_num[input_lines]) ) {
		input_lines++;
	}

	int x = 0;
	int y = 0;
	double angle = 0.0;
	for (int i = 0; i < input_lines; ++i) {
		switch (instr[i]) {
			case 'N': {y += i_num[i]; break;}
			case 'S': {y -= i_num[i]; break;}
			case 'W': {x -= i_num[i]; break;}
			case 'E': {x += i_num[i]; break;}
			case 'R': { angle -= (i_num[i] * M_PI) / (180.0); break;}
			case 'L': { angle += (i_num[i] * M_PI) / (180.0); break;}
			case 'F': {
				x += i_num[i] * (int)cos(angle);
				y += i_num[i] * (int)sin(angle);
			}
		}

	}
	part1_sum = abs(x) + abs(y);
	printf("Part1: %lld\n", part1_sum);

	x = 0;
	y = 0;
	int wx = 10;
	int wy = 1;
	for (int i = 0; i < input_lines; ++i) {
		switch (instr[i]) {
			case 'N': { wy += i_num[i]; break; }
			case 'S': { wy -= i_num[i]; break; }
			case 'W': { wx -= i_num[i]; break; }
			case 'E': { wx += i_num[i]; break; }
			case 'R': { rot_r( &wx, &wy, i_num[i] / 90 ); break; };
			case 'L': { rot_l( &wx, &wy, i_num[i] / 90 ); break; };
			case 'F': {
				x += wx * i_num[i];
				y += wy * i_num[i];
			}
		}

	}
	part2_sum = abs(x) + abs(y);
	printf("Part2: %lld\n", part2_sum);
}
