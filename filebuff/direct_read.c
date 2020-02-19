#define _GNU_SOURCE // Obtain O_DIRECT definition from <fcntl.h>
#include <fcntl.h>
// #include <malloc.h>
#include "../tlpi.h"

int
main(int argc, char *argv[]) {
	int fd;
	ssize_t nread;
	size_t length, alignment;
	off_t offset;
	char *buffer;

	if (argc < 3 || strcmp(argv[1], "--hlep") == 0) {
		usage_error("%s file length [offset [alignment]]\n", argv[0]);
	}

	length = get_long(argv[2], GN_ANY_BASE, "length");
	offset = (argc > 3) ? get_long(argv[3], GN_ANY_BASE, "offset") : 0;
	alignment = (argc > 4) ? get_long(argv[4], GN_ANY_BASE, "alignment") : 4096;

	fd = open(argv[1], O_RDONLY | O_DIRECT);
	if (fd == -1) {
		error_exit("open");
	}

	if (posix_memalign(&buffer, alignment * 2, length + alignment) != 0)  {
		error_exit("posix_memalign");
	}

	// buffer = memalign(alignment * 2, length + alignment);
	// if (buffer == NULL) {
	// 	error_exit("memalign");
	// }

	buffer += alignment;

	if (lseek(fd, offset, SEK_SET) == -1) {
		error_exit("lseek");
	}

	nread = read(fd, buffer, length);
	if (nread == -1) {
		error_exit("read");
	}

	printf("Read %ld bytes\n", (long)nread);

	return 0;
}