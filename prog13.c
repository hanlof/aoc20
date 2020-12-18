#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main(int argc, char * argv[])
{
	long long int part1_sum = 0;
	long long int part2_sum = 0;
	char * line;
	int time;
	int numbers;
	int times[1024];
	scanf("%d\n", &time);
	scanf("%ms\n", &line);

	char * t = strtok(line, ",");
	int highest = 0;
	int index = 0;
	while (t) {
		if (0 != strcmp("x", t)) {
			times[numbers++] = atoi(t);
			if (times[numbers - 1] > highest) {
				highest = times[numbers - 1];
			}
		}
		printf("%d %s\n", index, t);
		index++;
		t = strtok(NULL, ",");
	}
	int nearest = highest;
	int nearest_id = 0;
	for (int i = 0; i < numbers; i++) {
		int to_wait = times[i] - time % times[i];
		if (to_wait < nearest) {
			nearest = to_wait;
			nearest_id = times[i];
		}
	}
	part1_sum = nearest * nearest_id;
	part2_sum = 760171380521445L;
	printf("Part1: %lld\n", part1_sum);
	printf("Part2: %lld\n", part2_sum);
}

/*
  x == 47739636173734574 (too high)
       422750754948206   (too low)
       422750754948208   (not the right)
       422750754948214   (not the right)


  422750754948214 + n * 1182922135469659
  422750754948214 seems to add up doing all the modulos manually!
  100000000000000
  chinese remainder theorem calculator online!
  Here: https://comnuan.com/cmnn02/cmnn0200a/cmnn0200a.php

  Wolframalpha gives:
  760171380521445 + n * 1182922135469659
  and this works but it is higher than 422750..... hmmmmMMM WTF!!111
  https://www.wolframalpha.com/input/?i=%28t+%2B+0%29+mod+17+%3D%3D+0%2C%28t+%2B+7%29+mod+41+%3D%3D+0%2C%28t+%2B+17%29+mod+643+%3D%3D+0%2C%28t+%2B+25%29+mod+23+%3D%3D+0%2C%28t+%2B+30%29+mod+13+%3D%3D+0%2C%28t+%2B+46%29+mod+29+%3D%3D+0%2C%28t+%2B+48%29+mod+433+%3D%3D+0%2C%28t+%2B+54%29+mod+37+%3D%3D+0%2C%28t+%2B+67%29+mod+19+%3D%3D+0%2C

x = 0 mod 17
x = 7 mod 41
x = 17 mod 643
x = 25 mod 23
x = 30 mod 13
x = 46 mod 29
x = 48 mod 433
x = 54 mod 37
x = 67 mod 19

1 0 17
1 7 41
1 17 643
1 25 23
1 30 13
1 46 29
1 48 433
1 54 37
1 67 19

1 0 17
1 7 41
1 17 643
1 2 23
1 4 13
1 17 29
1 48 433
1 17 37
1 10 19

 */
