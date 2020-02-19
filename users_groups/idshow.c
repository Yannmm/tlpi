#define _GNU_SOURCE
#include <unistd.h>
#include <sys/fsuid.h>
#include <limits.h>
#include "ugid_functions.h"
#include "../tlpi.h"

#define SG_SIZE (NGROUPS_MAX + 1)

int main(int argc, char const *argv[])
{
	uid_t ruid, euid, suid, fsuid;
	gid_t rgid, egid, sgid, fsgid;
	gid_t supgroups[SG_SIZE];
	int gcount, j;
	char *p;

	if (getresuid(&ruid, &euid, &suid) == -1) {
		error_exit("getresuid");
	}
	if (getresgid(&rgid, &egid, &sgid) == -1) {
		error_exit("getresgid");
	}

	fsuid = setfsuid(0);
	fsgid = setfsgid(0);

	printf("UID: ");
	p = userNameFromId(ruid);
	printf("real=%s (%ld);", (p == NULL) ? "???" : p, (long)ruid);
	p = userNameFromId(euid);
	printf("eff=%s (%ld);", (p == NULL) ? "???" : p, (long)euid);
	p = userNameFromId(suid);
	printf("saved=%s (%ld);", (p == NULL) ? "???" : p, (long)suid);
	p = userNameFromId(fsuid);
	printf("fs=%s (%ld);", (p == NULL) ? "???" : p, (long)fsuid);
	printf("\n");

	printf("GID: ");
	p = groupNameFromId(rgid);
	printf("real=%s (%ld);", (p == NULL) ? "???" : p, (long)rgid);
	p = groupNameFromId(egid);
	printf("eff=%s (%ld);", (p == NULL) ? "???" : p, (long)egid);
	p = groupNameFromId(sgid);
	printf("saved=%s (%ld);", (p == NULL) ? "???" : p, (long)sgid);
	p = groupNameFromId(fsgid);
	printf("fs=%s (%ld);", (p == NULL) ? "???" : p, (long)fsgid);
	printf("\n");

	gcount = getgroupds(SG_SIZE, supgroups);
	if (gcount == -1) {
		error_exit("getgroups");
	}

	printf("Supplementary groups (%d): ", gcount);
	for (j = 0; j < gcount; j++) {
		p = groupNameFromId(supgroups[j]);
		printf("%s (%ld);", (p == NULL) ? "???" : p, (long)supgroups[j]);
	}
	printf("\n");

	return 0;
}