#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int main(int argc, char const *argv[], char *envp[])
{


	// char buffer[50];
	char *result = getenv("GIT_BINARY");

	size_t length = strlen(result);
	char copy[length + 1];
	char *end = strcpy(copy, result);

	if (putenv("kkk=bbb") != 0) {
		puts("出错啦");
	}

	char **p;
	for(p = environ; *p != NULL; p++) {
		printf("%s\n", *p);
	}

	// environ = NULL;
	if (clearenv() != 0) {

	}

	p = environ;
	p++;
	for(; *p != NULL; p++) {
		printf("%s\n", *p);
	}

	// printf("%s\n", copy);

	return 0;
}