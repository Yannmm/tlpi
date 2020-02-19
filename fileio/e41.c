#include "../tlpi.h"
// #include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	
	int o, mode;
	mode = O_TRUNC;
	while((o = getopt(argc, argv, "a")) > 0) {
		switch (o) {
			case 'a':
				mode = O_APPEND;
				break;
			default: usage_error("%s [-a] file\n", argv[0]);
		}
	}

	char *file = argv[optind];
	if (file == NULL) {
		usage_error("%s [-a] file\n", argv[0]);
	}


	while(1) {
		char *buffer = malloc(10000);
		ssize_t nread = read(STDIN_FILENO, buffer, 50);
		if (nread < 0) {
			error_exit("read");
		}
		buffer[nread] = '\0';

		int fd = open(file, O_RDWR | mode | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd < 0) { error_exit("open"); }

		printf("result is: %s", buffer);
		ssize_t nwritten = write(fd, buffer, strlen(buffer));
		if (nwritten < 0) { error_exit("write"); }
	}
	return 0;
}