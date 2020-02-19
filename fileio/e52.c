#include "../tlpi.h"
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (argc != 3 || strcmp(argv[1], "--help") == 0) {
		usage_error("%s filename text\n", argv[0]);
	}

	int fd = open(argv[1], O_RDWR | O_APPEND);
	if (fd == -1) {
		error_exit("open");
	}

	if (lseek(fd, 0, SEEK_SET) == -1) {
		error_exit("lseek");
	}

	ssize_t nwritten = write(fd, argv[2], strlen(argv[2]));
	if (nwritten == -1) {
		error_exit("write");
	}

	return 0;
}