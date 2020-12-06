
#include <stdio.h>
#include <string.h>

int yes_answers[50];
int main(int argc, char * argv[])
{
	char * tmp;
	int n;
	int totsum = 0;
	int allsum = 0;
	while (!feof(stdin)) {
		// When this loop condition is not met we started parsing on an
		// empty line (the first character we hit is NOT NOT '\n')
		for (int i = 0; i < 50; i++) {
			yes_answers[i] = 0;
		}
		int group_members = 0;
		while ((n = scanf("%m[^\n]", &tmp)) > 0) {
			// When the body of this look is entered we have one
			// valid line from the input in tmp.
			int j = 0;
			group_members++;
			while (tmp[j]) {
				int index = tmp[j];
				index -= 'a';
				yes_answers[index] += 1;
				j++;
			}

			(void) getchar(); // eat up the endline
		}
		for (int i = 0; i < 50; i++) {
			if (yes_answers[i]) totsum++;
			if (yes_answers[i] == group_members) allsum++;
		}
		(void) getchar(); // eat up the second endline (on empty lines)
	}
	printf("totsum: %d\n", totsum);
	printf("totsum: %d\n", allsum);
}
