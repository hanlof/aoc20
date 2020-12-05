#include <stdio.h>

int seat_id(char * s)
{
	int row = 0;
	if (s[0] == 'B') row += 64;
	if (s[1] == 'B') row += 32;
	if (s[2] == 'B') row += 16;
	if (s[3] == 'B') row += 8;
	if (s[4] == 'B') row += 4;
	if (s[5] == 'B') row += 2;
	if (s[6] == 'B') row += 1;

	int col = 0;
	if (s[7] == 'R') col += 4;
	if (s[8] == 'R') col += 2;
	if (s[9] == 'R') col += 1;

	return row * 8 + col;
}

int seats[1024] = { [0 ... 1023] = 0 };
int main(int argc, char * argv[])
{
	char * seat_string;
	int highest = 0;
	int lowest = 1024;
	int free_seat = 0;
	while ( 1 == scanf("%ms", &seat_string) ) {
		int t = seat_id(seat_string);
		if (t > highest) highest = t;
		if (t < lowest) lowest = t;
		seats[t] = 1;
	}
	for (int i = lowest; i <= highest; ++i) {
		if (seats[i] != 1) {
			free_seat = i;
		}
	}
	printf("Part1: %d\n", highest);
	printf("Part2: %d\n", free_seat);
}
