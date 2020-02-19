#include "my_error.h"
#include <sys/wait.h>

int main (int argc, char *argv[]) {
	int pfd[2];

	if (pipe(pfd) == -1) {
		my_eexit("pipe");
	}

	switch (fork()) {
		case -1: {
			my_eexit("fork");
		}
		case 0: {
			if (close(pfd[0]) == -1) {
				my_eexit("close 1");
			}

			if (pfd[1] != STDOUT_FILENO) {
				if (dup2(pfd[1], STDOUT_FILENO) == -1) {
					my_eexit("dup2 1");
				}
				if (close(pfd[1]) == -1) {
					my_eexit("close 2");
				}
			}

			execlp("ls", "ls", (char *)NULL);
			my_eexit("execlp ls");
		}

		default: {
			break;
		}
	}

	switch (fork()) {
		case -1: {
			my_eexit("fork");
		}
		case 0: {
			if (close(pfd[1]) == -1) {
				my_eexit("close 3");
			}

			if (pfd[0] != STDIN_FILENO) {
				if (dup2(pfd[0], STDIN_FILENO) == -1) {
					my_eexit("dup2 2");
				}
				if (close(pfd[0]) == -1) {
					my_eexit("close 4");
				}
			}

			execlp("wc", "wc", "-l", (char *)NULL);
			my_eexit("execlp wc");

		}
	}

	if (close(pfd[0]) == -1) {
		my_eexit("close 5");		
	}
	if (close(pfd[1]) == -1) {
		my_eexit("close 6");		
	}
	if (wait(NULL) == -1) {
		my_eexit("wait 1");		
	}
	if (wait(NULL) == -1) {
		my_eexit("wait 2");		
	}

	exit(EXIT_SUCCESS);
}