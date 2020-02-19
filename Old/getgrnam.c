#include <sys/types.h>
#include <grp.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	struct group *group;
	group = getgrnam("staff");
	if (group == NULL) {
		if (errno == 0) {
			puts("没找到");
		} else {
			puts("发生错误");
		}
	} else {
		printf("用户组为 %s(%ld)\n", group->gr_name, (long)group->gr_gid);
	}


}