#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int prog_length = 0;
int instrs[700] = { [ 0 ... 699] = 0 };
int values[700];
int visited[700] = { [ 0 ... 699] = 0 };

struct prog {
	int ip;
	int acc;
};

void run_prog(struct prog * p)
{
	for (int i = 0; i < prog_length; i++)
		visited[i] = 0;

	while ( !visited[p->ip] ) {
		visited[p->ip] = 1;
		if (instrs[p->ip] == 'n') { p->ip++; continue; }
		if (instrs[p->ip] == 'a') { p->acc += values[p->ip]; p->ip++; continue; }
		if (instrs[p->ip] == 'j') { p->ip += values[p->ip]; continue; }
		// no valid instruction encountered, means program terminated "normally"
		// by reaching past the last (valid) instruction.
		// can be checked by comparing p->ip to end of program
		return;
	}
}

void switch_instr(int n)
{
	if (instrs[n] == 'j') {
		instrs[n] = 'n';
	} else if (instrs[n] == 'n') {
		instrs[n] = 'j';
	}
}

int main(int argc, char * argv[])
{
	int part1_sum = 0;
	int part2_sum = 0;
	char * line;
	int i;
	int n = 0;
	while ( 2 == scanf("%ms %d", &line, &i) ) {
		instrs[n] = line[0];
		values[n] = i;
		n++;
	}
	prog_length = n;

	struct prog p = { .ip = 0, .acc = 0 };
	run_prog(&p);
	part1_sum = p.acc;
	for (i = 0; i < prog_length; i++) {
		switch_instr(i);
		p.ip = 0; p.acc = 0;
		run_prog(&p);
		if (p.ip >= prog_length) { part2_sum = p.acc; break; }
		switch_instr(i);
	}

	printf("Part1: %d\n", part1_sum);
	printf("Part2: %d\n", part2_sum);
}
