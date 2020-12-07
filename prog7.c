#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// This is the first version that solved the problem.
// This assignment may or may not ever be "upgraded" to use "proper" graph
// handling with dynamic element count and edge count.
// TODO?! Make proper graph handling functions.
#define MAKE_DOT 0

struct bag {
	char name[20];
	char contains[4][20];
	int contains_n[4];
	int contains_shinygold;
};

struct bag bags[600];

// finds (or adds) a bag struct by name
// if requested bag name (color) is not found then "create" it (by copying its
// name (color) to the first available slot in global bags array)
struct bag * find_bag(char * s)
{
	for (int i = 0; i < 600; i++) {
		if (!strcmp(bags[i].name, s)) return &bags[i];
	}
	// 
	for (int i = 0; i < 600; i++) {
		if (!strcmp(bags[i].name, "")) {
			strcpy(bags[i].name, s);
			return &bags[i];
		}
	}

	return NULL;
}

int count_children(struct bag * b)
{
	int children = 0;
	if (b->contains[0][0]) {

		children += b->contains_n[0];
		children += b->contains_n[0] * count_children(find_bag(b->contains[0]));
	}
	if (b->contains[1][0]) {
		children += b->contains_n[1];
		children += b->contains_n[1] * count_children(find_bag(b->contains[1]));
	}
	if (b->contains[2][0]) {
		children += b->contains_n[2];
		children += b->contains_n[2] * count_children(find_bag(b->contains[2]));
	}
	if (b->contains[3][0]) {
		children += b->contains_n[3];
		children += b->contains_n[3] * count_children(find_bag(b->contains[3]));
	}

	return children;
}

void part1_count(char * s)
{
	struct bag * b = find_bag(s);
	if (b->contains_shinygold) return;
	b->contains_shinygold = 1;
	for (int i = 0; i < 600; i++) {
		if (!strcmp(bags[i].contains[0], s)) { part1_count(bags[i].name); }
		if (!strcmp(bags[i].contains[1], s)) { part1_count(bags[i].name); }
		if (!strcmp(bags[i].contains[2], s)) { part1_count(bags[i].name); }
		if (!strcmp(bags[i].contains[3], s)) { part1_count(bags[i].name); }
	}
}

int main(int argc, char * argv[])
{
	for (int i = 0; i < 600; i++) {
		bags[i].name[0] = '\0';
		bags[i].contains_shinygold = 0;
		bags[i].contains_n[0] = 0;
		bags[i].contains_n[1] = 0;
		bags[i].contains_n[2] = 0;
		bags[i].contains_n[3] = 0;
		bags[i].contains[0][0] = '\0';
		bags[i].contains[1][0] = '\0';
		bags[i].contains[2][0] = '\0';
		bags[i].contains[3][0] = '\0';
	}
	char * c1;
	char * c2;
	char * c3;
	char * c4;
	int n1;
	char delim;
	if (MAKE_DOT) {
		printf("digraph prog7 {\n");
	}
	while ( 2 == scanf("%ms %ms bags contain", &c1, &c2) ) {
		char name[50] = "";
		strcat(name, c1);
		strcat(name, c2);
		struct bag * b = find_bag(name);
		int n = 0;
		int index = 0;
		while ( 4 == (n = scanf("%d %ms %ms bag%c", &n1, &c3, &c4, &delim)) ) {
			char name[50] = "";
			strcat(name, c3);
			strcat(name, c4);
			if (MAKE_DOT) {
				printf("  %s%s -> %s%s;\n", c1, c2, c3, c4);
			}
			strcpy(b->contains[index], name);
			b->contains_n[index] = n1;
			index++;
			if (delim == 's')
				delim = getchar();
			if (delim == '.')
				break;
		}
		if (n != 4) { scanf("no other bags.");  }
	}

	if (MAKE_DOT) {
		printf("  shinygold [color=red];\n");
		printf("}\n");
		exit(0);
	}
	int part1_sum = 0;
	int part2_sum = 0;
	part1_count("shinygold");
	for (int i = 0; i < 600; i++) {
		if (bags[i].contains_shinygold) part1_sum++;
	}
	part1_sum--; // because shinygold itself is marked as containing shinygold because reasons
	printf("Part1: %d\n", part1_sum);
	struct bag * b = find_bag("shinygold");
	part2_sum = count_children(b);
	printf("Part2: %d\n", part2_sum);
}
