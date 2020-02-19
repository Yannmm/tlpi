#include "../tlpi.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
	size_t length;
	off_t offset;
	int fd, ap, j;
	char *buffer;
	ssize_t nread, nwritten;
	if (argc < 3 || strcmp(argv[1], "--help") == 0) {
		usage_error("%s file {r<length>|R<length>|w<string>|s<offset>}...\n", argv[0]);
	}
	fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1) {
		error_exit("open");
	}

	for (ap = 2; ap < argc; ap++) {
		switch (argv[ap][0]) {
			case 'r':
			case 'R': {
				length = get_long(&argv[ap][1], GN_ANY_BASE, argv[ap]);
				buffer = malloc(length);
				if (buffer == NULL) {
					error_exit("malloc");
				}
				nread = read(fd, buffer, length);
				if (nread == -1) {
					error_exit("read");
				}
				if (nread == 0) {
					printf("%s: end-of-file\n", argv[ap]);
				} else {
					printf("%s: ", argv[ap]) ;
					for (j = 0; j < nread; j++) {
						if (argv[ap][0] == 'r') {
							printf("%c", isprint((unsigned char)buffer[j]) ? buffer[j] : '?');
						} else {
							printf("%02x ", (unsigned int)buffer[j]);
						}
					}
					printf("\n");
				}
				free(buffer);
				break;
			}
			case 'w': { // write string at current offset.
				nwritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
				if (nwritten == -1) {
					error_exit("write");
				}
				printf("%s: wrote %ld bytes\n", argv[ap], (long)nwritten);
				break;
			}
			case 's': { // change file offset
				offset = get_long(&argv[ap][1], GN_ANY_BASE, argv[ap]);
				if (lseek(fd, offset, SEEK_SET) == -1) {
					error_exit("lseek");
				}
				printf("%s: seek succeeded\n", argv[ap]);
				break;
			}
			default: {
				cmdl_error("Argument must start with [rRws]: %s\n", argv[ap]);
			}
		}
	}
	exit(EXIT_SUCCESS);
}