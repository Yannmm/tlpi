#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "my_error.h"

int main(int argc, char *argv[]) {

	int istack = 222;

	switch (vfork()) {
		case -1: {
			my_eexit("vfork()");
		}
		case 0: {
			sleep(2);
			write (STDOUT_FILENO, "Child executing\n", 16);
			istack *= 3;
			exit(0);
		}
		default: {
			write(STDOUT_FILENO, "Parent executing\n", 17);
			printf("istack=%d\n", istack);
			exit(0);
		}
	}

	return 0;
}