#include "../tlpi.h"
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (argc < 3 || strcmp(argv[1], "--help") == 0) {
		usage_error("%s source destination\n", argv[0]);
	}

	int sourcef = open(argv[1], O_RDONLY);
	int destf = open(argv[2], O_WRONLY)	;
	char *buffer = malloc(50);
	
	int nread;
	while((nread = read(sourcef, buffer, 50)) > 0) {
		int nwritten = write(destf, buffer, nread);
		if (nwritten < 0) {
			error_exit("write");
		}
	}
	if (nread < 0) {
		error_exit("read");
	}
	return 0;
}