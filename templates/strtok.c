#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[])
{
	char tmp[] = "a b c d ddd k";

	char * t = strtok(tmp, " ");
	while (t) {
		printf("%s\n", t);
		t = strtok(NULL, " ");
	}

}
