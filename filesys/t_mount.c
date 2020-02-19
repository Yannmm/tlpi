#include <sys/param.h>
#include <sys/mount.h>
#include "../tlpi.h"

static void
MNT_usage_error(const char *pname, const char *msg) {
	if (msg != NULL) {
		fprintf(stderr, "%s", msg);
	}
	fprintf(stderr, "Usage: %s [options] source target\n\n", pname);
	fprintf(stderr, "Available options:\n");

	#define fpe(str) fprintf(stderr, "		" str) // shorter
	fpe("-t fstype		[e.g., 'ext2' or 'reiserfs']\n");
	fpe("-o data		[file system-dependent options, \n");
	fpe("				e.g., 'bsdgroups' for ext2]\n");
	fpe("-f mountflags can include any of: \n");

	#define fpe2(str) fprintf(stderr, "		" str);
	fpe2("b - MNT_BIND		create a bind mount\n");
	fpe2("d - MNT_DIRSYNC	synchronous directory updates\n");
	fpe2("l - MNT_MANDLOCK	permit mandatory locking\n");
	fpe2("m - MNT_MOVE		atomically move subtree\n");
	fpe2("A - MNT_NOATIME	don't update last access time\n");
	fpe2("V - MNT_NODEV		don't permit device access\n");
	fpe2("D - MNT_NODIRATIME	don't update access time on direcories\n");
	fpe2("E - MNT_NOEXEC		don't allow executacubles\n");
	fpe2("S - MNT_NOSUID		disable set-user/group-ID programs\n");
	fpe2("r - MNT_RDONLY		read-only mount\n");
	fpe2("c - MNT_REC		recursive mount\n");
	fpe2("R - MNT_REMOUNT	remount\n");
	fpe2("s - MNT_SYNCHRONUS	make wirtes synchronous\n");

	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	unsigned long flags;
	char *data, *fstype;
	int j, opt;
	flags = 0;
	data = NULL;
	fstype = NULL;

	while((opt = getopt(argc, argv, "o:t:f:")) != -1) {
		switch (opt) {
			case 'o':
			data = optarg;
			break;
			case 't':
			fstype = optarg;
			case 'f':
			for(j = 0; j < strlen(optarg); j++) {
				switch(optarg[j]) {
					case 'b': flags |= MNT_BIND;
					case 'd': flags |= MNT_DIRSYNC;
					case 'l': flags |= MNT_MANDLOCK;
					case 'm': flags |= MNT_MOVE;
					case 'A': flags |= MNT_NOATIME;
					case 'V': flags |= MNT_NODEV;
					case 'D': flags |= MNT_NODIRATIME;
					case 'E': flags |= MNT_NOEXEC;
					case 'S': flags |= MNT_NOSUID;
					case 'r': flags |= MNT_RDONLY;
					case 'c': flags |= MNT_REC;
					case 'R': flags |= MNT_REMOUNT;
					case 's': flags |= MNT_SYNCHRONUS;
					default: MNT_usage_error(argv[0], NULL);
				}
			}
			break;
			default:
			MNT_usage_error(argv[0], NULL);
		}
	}

	if (argc != optind + 2) {
		MNT_usage_error(argv[0], "Wrong number of arguments\n");
	}

	if (mount(argv[optind], argv[optind + 1], fstype, flags, data) == -1) {
		error_exit("mount");
	}

	exit(EXIT_SUCCESS);
}