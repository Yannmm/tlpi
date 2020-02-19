// #define _LARGEFILE64_SOURCE
#ifdef __APPLE__
#define off64_t off_t
#define open64 open
#define lseek64 lseek
#endif

#include <sys/stat.h>
#include <fcntl.h>
#include "../tlpi.h"

int main(int argc, char const *argv[])
{
	int fd;
	off64_t offset;
	if (argc != 3 || strcmp(argv[1], "--help") == 0) {
		usage_error("%s pathname offset\n", argv[0]);
	}
	fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		error_exit("open64");
	}
	offset = atoll(argv[2]);
	if (lseek64(fd, offset, SEEK_SET) == -1) {
		error_exit("lseek64");
	}
	if (write(fd, "test", 4) == -1) {
		error_exit("write");
	}
	exit(EXIT_SUCCESS);
	return 0;
}