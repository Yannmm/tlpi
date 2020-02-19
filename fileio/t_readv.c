#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "../tlpi.h"

int main(int argc, char const *argv[])
{
	int fd, x;
	struct iovec iov[3];
	struct stat mine;

	#define STR_SIZE 100
	char str[STR_SIZE];
	ssize_t nread, total;

	if (argc != 2 || strcmp(argv[1], "--help") == 0) {
		usage_error("%s file\n",argv[0]);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		error_exit("open");
	}

	total = 0;

	iov[0].iov_base = &mine;
	iov[0].iov_len = sizeof(struct stat);
	total += iov[0].iov_len;

	iov[1].iov_base = &x;
	iov[1].iov_len = sizeof(x);
	total += iov[1].iov_len;

	iov[2].iov_base = str;
	iov[2].iov_len = STR_SIZE;
	total += iov[2].iov_len;

	nread = readv(fd, iov, 3);
	if (nread == -1) {
		error_exit("readv");
	}
	if (nread < total) {
		printf("read fewer bytes than requested\n");
	}

	printf("total bytes requested: %ld; bytes red: %ld\n", (long)total, (long)nread);

	return 0;
}
