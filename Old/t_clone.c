
#define _GNU_SOURCE
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sched.h>
#include "my_error.h"

#ifndef CHILD_SIG
#define CHILD_SIG SIGUSR1
#endif

static int child_func(void *arg) {
	if (close(*((int *)arg)) == -1) {
		my_eexit("close");
	}
	return 0;
}

int main (int argc, char *argv[]) {
	const int stack_size = 65536;
	char *stack;
	char *stack_top;
	int s, fd, flags;

	fd = open("/dev/null", O_RDWR);
	if (fd == -1) {
		my_eexit("open");
	}

	flags = (argc > 1) ? CLONE_FILES : 0;

	stack = malloc(STACK_SIZE);
	if (stack == NULL) {
		my_eexit("malloc");
	}
	stack_top = stack + STACK_SIZE;

	if (CHILD_SIG != 0 && CHILD_SIG != SIGCHLD) {
		if (signal(CHILD_SIG, SIG_IGN) == SIG_ERR) {
			my_eexit("signal");
		}
	}

	if (clone(child_func, stack_top, flags | CHILD_SIG, (void *)&fd) == -1) {
		my_eexit("clone");
	}

	if (waitpid(-1, NULL, (CHILD_SIG != SIGCHLD) ? __WCLONE : 0) == -1) {
		my_eexit("waitpid");
	}
	printf("child has terminated\n");

	s = write(fd, "x", 1);
	if (s == -1 && errno == EBADF) {
		printf("file descriptor %d has been closed\n", fd);
	} else if (s == -1) {
		printf("write() on file descriptor %d failed", "unexpectedly (%s)\n", fd, strerror(errno));
	} else {
		printf("write() on file descriptor %d succeeded\n", fd);
	}

	exit(EXIT_SUCCESS);
}