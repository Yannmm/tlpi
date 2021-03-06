#include <sys/stat.h>
#include <fcntl.h>
#include "../tlpi.h"

#ifndef BUF_SIZE 
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {
	int old, new, flags;
	mode_t permissions;
	ssize_t nread;
	char buf[BUF_SIZE];

	if (argc != 3 || strcmp(argv[1], "--help") == 0) {
		printf("usage error: %s old-file new-file\n", argv[0]);
		return -1;
	}

	old = open(argv[1], O_RDONLY);
	if (old == -1) {
		printf("opning file %s", argv[1]);
		return -1;
	}

	flags = O_CREAT | O_WRONLY | O_TRUNC | O_SYNC;
	permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	new = open(argv[2], flags, permissions);
	if (new == -1) {
		printf("opning file %s", argv[1]);
		return -1;
	}

	while((nread = read(old, buf, BUF_SIZE)) > 0) {
		if (write(new, buf, nread) != nread) {
			printf("fatal: could write whole buffer\n");
		}
	}

	if (nread == -1) {
		printf("read\n");
		return -1;
	}

	if (close(old) == -1) {
		puts("close input");
		return -1;
	}
	if (close(new) == -1) {
		puts("close output");
		return -1;
	}
	exit(EXIT_SUCCESS);
}
