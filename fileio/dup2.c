#include "../handle_error.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	// int newfd = dup2(STDIN_FILENO, 10000);
	int newfd = fcntl(STDOUT_FILENO, F_DUPFD, 200);
	if (newfd < 0) {
		error_exit("fcntl");
	}
	printf("the new fd is: %d\n", newfd);
	return 0;
}