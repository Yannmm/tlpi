#include <pwd.h>
#include <grp.h>
#include "../users_groups/ugid_functions.h"

#include "../tlpi.h"

int
main(int argc, char *argv[]) {
	uid_t uid;
	gid_t gid;
	int j;
	Boolean errFnd;

	if (argc < 3 || strcmp(argv[1], "--help") == 0) {
		usage_error("%s owner group [file...]\n" "		owner or group can be '-', "
			"meaning leave unchanged\n", argv[0]);
	}

	if (strcmp(argv[1], "-") == 0) {
		uid = -1;
	} else {
		uid = userIdFromName(argv[1]);
		if (uid == -1) {
			fatal("No such user (%s)", argv[1]);
		}
	}

	if (strcmp(argv[2], "-") == 0) {
		gid = -1;
	} else {
		gid = groupIdFromName(argv[2]);
		if (gid == -1) {
			fatal("No group user (%s)", argv[2]);
		}
	}

	errFnd = false;
	for (j = 3; j < argc; j++) {
		if (chown(argv[j], uid, gid) == -1) {
			error_message("chown: %s", argv[j]);
			errFnd = true;
		}
	}

	exit(errFnd ? EXIT_FAILURE : EXIT_SUCCESS);
}