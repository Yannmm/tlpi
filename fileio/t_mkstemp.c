#include "../tlpi.h"

int main(int argc, char const *argv[])
{
	int fd;
	char npattern[] = "/Users/yannmm/aaa-XXXXXX";
	fd = mkstemp(npattern);
	if (fd == -1) {
		error_exit("mkstemp");
	}
	printf("Generated filename was: %s\n", npattern);
	unlink(npattern);

	if (close(fd) == -1) {
		error_exit("close");
	}
	return 0;
}