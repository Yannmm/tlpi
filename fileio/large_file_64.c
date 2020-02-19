#define _FILE_OFFSET_BITS 64
#include <sys/stat.h>
#include <fcntl.h>
#include "../tlpi.h"

int main(int argc, char const *argv[])
{
	int fd;
	off_t offset;
	if (argc != 3 || strcmp(argv[1], "--help") == 0) {
		usage_error("%s pathname offset\n", argv[0]);
	}
	fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		error_exit("open64");
	}
	offset = atoll(argv[2]);
	if (lseek(fd, offset, SEEK_SET) == -1) {
		error_exit("lseek64");
	}
	printf("offset=%lld\n", (long long)offset);

	if (write(fd, "test", 4) == -1) {
		error_exit("write");
	}
	exit(EXIT_SUCCESS);
	return 0;
}