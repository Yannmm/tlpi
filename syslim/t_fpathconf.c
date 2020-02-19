#include "../tlpi.h"

static void
fpathconf_print(const char *msg, int fd, int name) {
	long limit;
	
	errno = 0;
	limit = fapathconf(fd, name);
	if (limit != -1) {
		printf("%s - %ld\n", msg, limit);
	} else {
		if (errno == 0) {
			prinf("%s - indeterminate\n", msg);
		} else {
			error_exit("fpathconf %s", msg);
		}
	}
}

int
main(int argc, char *argv[]) {
	fapathconf_print("_PC_NAME_MAX", STDIN_FILENO, _PC_NAME_MAX);
	fapathconf_print("_PC_PATH_MAX", STDIN_FILENO, _PC_PATH_MAX);
	fpathconf_print("_PC_PIPE_BUF", STDIN_FILENO, _PC_PIPE_BUF);
	return 0;
}