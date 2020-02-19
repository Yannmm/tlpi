#include "../tlpi.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (argc < 2 || strcmp(argv[1], "--help") == 0) {
		usage_error("%s file\n", argv[0]);
	}

	int fd1 = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	int fd2 = dup(fd1);
	int fd3 = open(argv[1], O_RDWR);
	write(fd1, "Hello,", 6);
	write(fd2, " world", 6);
	lseek(fd2, 0 , SEEK_SET);
	write(fd1, "HELLO,", 6);
	write(fd3, "Gidday", 6);


	char buffer[50];
	lseek(fd1, 0, SEEK_SET);
	ssize_t nread = read(fd1, buffer, 50);
	buffer[nread] = '\0';
	printf("结果为 %s\n", buffer);
	return 0;
}