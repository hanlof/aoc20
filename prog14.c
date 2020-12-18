#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

// this works! but it takes several seconds to run but who cares?! LOL
int accumulated_xcount = 0;
long long int parse_mask(char * mask, char ch)
{
	long long unsigned int t = (1L<<35L);
	long long unsigned int out = 0;
	int i = 0;
	int xcount = 0;
	while (mask[i]) {
		if (mask[i] == 'X') xcount++;
		if (mask[i] == ch) {
			out += t;
		}
		t = t >> 1;
		i++;
	}
	accumulated_xcount += 1 << xcount;
	//printf("xcount %d %d\n", 1 << xcount, accumulated_xcount);

	return out;
}

int input_lines = 0;
int max_position = 0;
long long int mem[100000] = { [ 0 ... 99999 ] = 0 };
long long int positions[2*65536] = { [ 0 ... 2*65536-1 ] = 0 };
long long int values[2*65536] = { [ 0 ... 2*65536-1 ] = 0 };

void update_mem(long long int pos, long long int value)
{
	for (int i = 0; i < max_position; i++) {
		if (positions[i] == pos) {
			values[i] = value;
			return;
		}
	}
	// didnt find value for position pos. make new entry
	positions[max_position] = pos;
	values[max_position] = value;
	max_position++;
}

void apply_x(char * mask, long long int base_pos2, long long int val)
{
	long long unsigned int t = (1LL << 35LL);
	int i = 0;
	long long int temp = base_pos2;
	while (mask[i]) {
		if (mask[i] == 'H') temp |= t;
		if (mask[i] == 'L') temp &= ~t;
		if (mask[i] == 'X') {
			mask[i] = 'H';
			apply_x(mask, base_pos2, val);
			mask[i] = 'L';
			apply_x(mask, base_pos2, val);
			mask[i] = 'X';
			return;
		}

		t = t >> 1;
		i++;
	}

	update_mem(temp, val);
//	printf("%s %lld %lld %lld\n", mask, base_pos2, temp, val);
}

int main(int argc, char * argv[])
{
	long long int part1_sum = 0;
	long long int part2_sum = 0;
	char * command;
	char * operator;
	char * mask = "";
	long long int or_mask = 0;
	long long int and_mask = 0;
	while ( 2 == scanf("%ms = %ms", &command, &operator) ) {
		if (!strncmp("mem", command, 3)) {
			long long int pos = atoi(&command[4]);
			long long int val = atoi(&operator[0]);
			// part 1
			val |= or_mask;
			val &= and_mask;
			mem[pos] = val;

			// part2
			// count X:es in mask
			// iterate N from 0...(1 << X) times
			// for each N replace each x with corresponding
			// bit from N.  and update_mem() with that pos.
			// also apply the bitmasking
			long long int base_pos2 = pos;
			base_pos2 |= or_mask;
//			printf("%s %llx\n", mask, base_pos2);
			apply_x(mask, base_pos2, atoi(&operator[0]));
		} else if (!strncmp("mask", command, 4)) {
			or_mask = parse_mask(operator, '1');
			and_mask = ~parse_mask(operator, '0');
			and_mask = and_mask & ((1L<<36L) - 1);
			mask = operator;
		}
		input_lines++;
	}
	for (int i = 0; i < 100000; i++) {
		part1_sum += mem[i];
	}

	for (int i = 0; i < max_position; i++) {
		part2_sum += values[i];
	}

	// 1576953804222 too low!
	// 1819911361394 too low!
	printf("Part1: %lld\n", part1_sum);
	printf("Part2: %lld\n", part2_sum);
}
// duplicate addresses are present in input
// memory addresses in input are < 0xffff
