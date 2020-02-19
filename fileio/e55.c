#include "../tlpi.h"
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (argc < 2 || strcmp(argv[1], "--help") == 0) {
		usage_error("%s file\n", argv[0]);
	}

	int fd1 = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd1 == -1) {
		error_exit("open");
	}

	int fd2 = dup(fd1);

	off_t offset1 = lseek(fd1, 150, SEEK_SET);
	off_t offset2 = lseek(fd2, 0, SEEK_CUR);

	int flag1 = fcntl(fd1, F_GETFL);
	int flag2 = fcntl(fd2, F_GETFL);

	printf("fd1 is %d, offset is %lld, flag is %d\n", fd1, (long long)offset1, flag1);
	printf("fd2 is %d, offset is %lld, flag is %d\n", fd2, (long long)offset2, flag2);

	return 0;
}