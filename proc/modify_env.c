#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../tlpi.h"

extern char **environ;

int main(int argc, char *argv[])
{
	int j;
	char **ep;

	// osx 中缺少 clearenv() 这个函数
	// 直接置空 envrion，而 putenv 却不会恢复 evnrion，会导致内存访问错误
	envrion = NULL;


	
	for(j = 1; j < argc; j++) {

		char *buffer = malloc(strlen(argv[j]) + 1);
		if (buffer == NULL) {
			error_exit("malloc");
		}
		strcpy(buffer, argv[j]);
		printf("---> %s\n", buffer);

		if (putenv(buffer) !=0 ) {
			// error_exit("putenv: %s", argv[j]);
		}
	}


	if (setenv("GREET", "Hello World", 0) == -1) {
		error_exit("setevn");
	}

	unsetenv("BYE");


	for (ep = environ; *ep != NULL; ep++) {
		puts(*ep);
	}

	return 0;
}