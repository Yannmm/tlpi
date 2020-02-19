#include "../tlpi.h"
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (argc < 4 || strcmp(argv[1], "--help") == 0) {
		usage_error("%s filename num-bytes string [x]\n", argv[0]);
	}

	int flags = 0;
	if (argc < 5) {
		flags = O_RDWR | O_CREAT | O_APPEND;
	} else {
		flags = O_RDWR | O_CREAT;
	}

	int fd = open(argv[1], flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1) {
		error_exit("open");
	}

	int count = get_int(argv[3], GN_ANY_BASE, argv[3]);

	char k[20];
	strcpy(k, argv[2]);
	printf("arg is %s\n", k);

	if (argc < 5) {
		for(int i = 0; i < count; i++) {
			ssize_t nwritten = write(fd, k, strlen(k));
			if (nwritten == -1) {
				error_exit("nwritten");
			}
		}
	} else {
		for(int i = 0; i < count; i++) {
			off_t offset = lseek(fd, 0, SEEK_END);
			if (offset == -1) {
				error_exit("lseek");
			}
			ssize_t nwritten = write(fd, k, strlen(k));
			if (nwritten == -1) {
				error_exit("nwritten");
			}
		}
	}	

	return 0;
}