#include <sys/stat.h>
#include <fcntl.h>
#include "fpemns.h"
#include "../tlpi.h"

#define MYFILE "myfile"
#define MYDIR "mydir"
#define FILE_PERMS		(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define DIR_PERMS		(S_IRWXU | S_IRWXG | S_IRWXO)
#define UMASK_SETTING	(S_IWGRP | S_IXGRP | S_IWOTH | S_IXOTH)

int
main(int argc, char * argv[]) {
	int fd;
	struct stat sb;
	mode_t u;

	umask(UMASK_SETTING);

	fd = open (MYFILE, O_RDWR | O_CREAT | O_EXCL, FILE_PERMS);
	if (fd == -1) {
		error_exit("open-%s", MYFILE);
	}
	if (mkdir(MYDIR, DIR_PERMS) == -1) {
		error_exit("mkdir-%s", MYDIR);
	}

	u = umask(0);

	if (stat(MYFILE, &sb) == -1) {
		error_exit("stat-%s", MYFILE);
	}

	printf("Requestd file perms: %s\n", fpemnstring(FILE_PERMS, 0));
	printf("Process mask: %s\n", fpemnstring(u, 0));
	printf("Actual file perms: %s\n\n", fpemnstring(sb.st_mode, 0));

	if (stat(MYDIR, &sb) == -1) {
		error_exit("stat-%s", MYDIR);
	}

	printf("Requestd file perms: %s\n", fpemnstring(DIR_PERMS, 0));
	printf("Process mask: %s\n", fpemnstring(u, 0));
	printf("Actual file perms: %s\n\n", fpemnstring(sb.st_mode, 0));

	if (unlink(MYFILE) == -1) {
		error_message("unlink-%s", MYFILE);
	}
	if (rmdir(MYDIR) == -1) {
		error_message("rmdir-%s", MYDIR);
	}
	exit(EXIT_SUCCESS);
}