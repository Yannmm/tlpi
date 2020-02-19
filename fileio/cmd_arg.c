// #include "../tlpi.h"
#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>

extern char *program_invocation_name;
extern char *program_invocation_short_name;

int main(int argc, char const *argv[])
{
	char const **p;
	for(p = argv; *p != NULL; p++) {
		printf("%s\n", *p);
	}

	printf("文件名为 - %s\n", program_invocation_name);

	return 0;
}