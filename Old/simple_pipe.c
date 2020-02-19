#include "my_error.h"
#include <sys/wait.h>

#define BUF_SIZE 10

int main(int argc, char *argv[]) {
	int pdf[2];
	char buf[BUF_SIZE];
	ssize_t nRead;

	if (argc != 2 || strcmp(argv[1], "--help") == 0) {
		my_eexit("参数错误");
	}

	if (pipe(pdf) == -1) {
		my_eexit("pipe");
	}

	switch (fork()) {
		case -1: {
			my_eexit("fork");
		}
		case 0: {
			if (close(pdf[1]) == -1) {
				my_eexit("close - child");
			}

			for (;;) {
				nRead = read(pdf[0], buf, BUF_SIZE);
				if (nRead == -1) {
					my_eexit("read");
				}

				if (nRead == 0) {
					break;
				}

				if (write(STDOUT_FILENO, buf, nRead) != nRead) {
					my_eexit("child - partial/failed write");
				}
			}

			write(STDOUT_FILENO, "\n", 1);
			if (close(pdf[0]) == -1) {
				my_eexit("close");
			}
		}
		default: {
			if (close(pdf[0]) == -1) {
				my_eexit("close - parent");
			}

			if (write(pdf[1], argv[1], strlen(argv[1])) != strlen(argv[1])) {
				my_eexit("parent - partial/failed write");
			}
			if (close(pdf[1]) == -1) {
				my_eexit("close");
			}
			wait(NULL);
			exit(EXIT_SUCCESS);
		}
	}
}