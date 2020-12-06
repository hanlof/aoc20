#include <stdio.h>
#include <string.h>

#define BYR (1 << 0)
#define IYR (1 << 1)
#define EYR (1 << 2)
#define HGT (1 << 3)
#define HCL (1 << 4)
#define ECL (1 << 5)
#define PID (1 << 6)
#define CID (1 << 7)
#define REQ (BYR | IYR | EYR | HGT | HCL | ECL | PID)

int validate_byr(char * input)
{
	int val;
	if (!sscanf(input, "byr:%4d", &val)) printf("PANIC!");
	int ok = (val >= 1920 && val <= 2002);
	return ok;
}

int validate_iyr(char * input)
{
	int val;
	if (!sscanf(input, "iyr:%4d", &val)) printf("PANIC!");
	int ok = (val >= 2010 && val <= 2020);
	return ok;
}

int validate_eyr(char * input)
{
	int val;
	if (!sscanf(input, "eyr:%4d", &val)) printf("PANIC!");
	int ok = (val >= 2020 && val <= 2030);
	return ok;
}

int validate_hgt(char * input)
{
	int val;
	char * unit;
	if (1 > sscanf(input, "hgt:%d%ms", &val, &unit)) printf("PANIC!");
	if (!unit) return 0;
	if (!strncmp(unit, "cm", 2)) {
		return (val >= 150 && val <= 193);
	} else if (!strncmp(unit, "in", 2)) {
		return (val >= 59 && val <= 76);
	}
	return 0;
}

int validate_hcl(char * input) {
	//a # followed by exactly six characters 0-9 or a-f.
	char c;
	char * hex;
	if (2 != sscanf(input, "hcl:%[#]%ms", &c, &hex)) { return 0; }
	if (strlen(hex) != 6) { return 0; }
	for (int i = 0; i < 6; ++i) {
		if ( (hex[i] >= '0' && hex[i] <= '9') ||
		     (hex[i] >= 'a' && hex[i] <= 'f') ) {
			continue;
		} else {
			return 0;
		}
	}
	return 1;
}

int validate_ecl(char * input) {
	// exactly one of: amb blu brn gry grn hzl oth.
	char * col;
	if (1 != sscanf(input, "ecl:%ms", &col)) { return 0; }
	if (!strncmp(col, "amb", 3)) return 1;
	if (!strncmp(col, "blu", 3)) return 1;
	if (!strncmp(col, "brn", 3)) return 1;
	if (!strncmp(col, "gry", 3)) return 1;
	if (!strncmp(col, "grn", 3)) return 1;
	if (!strncmp(col, "hzl", 3)) return 1;
	if (!strncmp(col, "oth", 3)) return 1;

	return 0;
}

int validate_pid(char * input) {
	// a nine-digit number, including leading zeroes.
	char * pid;
	if (1 != sscanf(input, "pid:%ms", &pid)) { return 0; }
	if (strlen(pid) != 9) { return 0; }
	for (int i = 0; i < 9; ++i) {
		if ( (pid[i] >= '0' && pid[i] <= '9')) {
			continue;
		} else {
			return 0;
		}
	}

	return 1;
}

int main(int argc, char * argv[])
{
	char * tmp;
	int n;
	int part1count = 0;
	int part2count = 0;
	while (!feof(stdin)) {
		int found = 0;
		int valid = 1;
		// When this loop condition is not met we started parsing on an
		// empty line (the first character we hit is NOT NOT '\n')
		while ((n = scanf("%m[^\n]", &tmp)) > 0) {
			// When the body of this look is entered we have one
			// valid line from the input in tmp.
			// Tokenize it and handle each part of each line in the
			// inner loop.
			char * t = strtok(tmp, " ");
			while (t) {
				if             (!strncmp(t, "byr", 3)) {
					found |= BYR;
					valid &= validate_byr(t);
				} else if      (!strncmp(t, "iyr", 3)) {
					found |= IYR;
					valid &= validate_iyr(t);
				} else if      (!strncmp(t, "eyr", 3)) {
					found |= EYR;
					valid &= validate_eyr(t);
				} else if      (!strncmp(t, "hgt", 3)) {
					found |= HGT;
					valid &= validate_hgt(t);
				} else if      (!strncmp(t, "hcl", 3)) {
					found |= HCL;
					valid &= validate_hcl(t);
				} else if      (!strncmp(t, "ecl", 3)) {
					found |= ECL;
					valid &= validate_ecl(t);
				} else if      (!strncmp(t, "pid", 3)) {
					found |= PID;
					valid &= validate_pid(t);
				} else if      (!strncmp(t, "cid", 3)) {
					found |= CID;
				}
				t = strtok(NULL, " ");
			}
			(void) getchar(); // eat up the endline
		}
		if ((REQ & found) == REQ) {
			part1count++;
			if (valid) part2count++;
		}
		(void) getchar(); // eat up the second endline (on empty lines)
	}
	printf("Part1: %d\n", part1count);
	printf("Part2: %d\n", part2count);
}
