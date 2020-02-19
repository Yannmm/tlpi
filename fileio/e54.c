#include "../tlpi.h"
#include <fcntl.h>

static int my_dup(int oldfd) {
	int fd = fcntl(oldfd, F_DUPFD, 0);
	return fd;
}

static int my_dup2(int oldfd, int newfd) {
	if (fcntl(oldfd, F_GETFL) == -1) {
		errno = EBADF;
		return -1;
	}
	if (oldfd == newfd) {
		return newfd;
	}
	if (close(newfd) == -1) {
		return -1;
	}
	int fd = fcntl(oldfd, F_DUPFD, newfd);
	return fd;
}

int main(int argc, char const *argv[])
{
	int fd1 = my_dup(0);
	if (fd1 == -1) {
		error_exit("my_dup");
	}
	printf("fd1 is %d\n", fd1);
	puts("----------");

	int fd2 = my_dup2(1, 2);
	printf("fd2 is %d\n", fd2);

	return 0;
}