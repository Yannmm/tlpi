#include <fcntl.h>
#include "../tlpi.h"

#define MAX_LINE 100

int
main(int argc, char *argv[]) {
	int fd;
	char line[MAX_LINE];
	ssize_t n;
	
	fd = open("/proc/sys/kernel/pid_max", (argc > 1) ? O_RDWR : O_RDONLY);
	if (fd == -1) {
		error_exit("open");
	}
	
	n = read(fd, line, MAX_LINE);
	
	if (n == -1) {
		error_exit("read");
	}
	
	if (argc > 1) {
		printf("Old value:	");
	}
	printf("%*s", (int)n, line);
	
	if (argc > 1) {
		if (lseek(fd, 0, SEEK_SET) == -1) {
			error_exit("lseek");
		}
		
		if (write(fd, argv[1], strlen(argv[1])) != strlen(argv[1])) {
			error_exit("write() failed");
		}
		system("echo /proc/sys/kernel/pid_max now contains " "`cat /proc/sys/kernel/pid_max`");
	}
	
	return 0;
}