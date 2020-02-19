#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	struct passwd *password;
	password = getpwnam("ryan");
	if (password == NULL) {
		if (errno == 0) {
			puts("没找到");
		} else {
			puts("发生错误");
		}
	} else {
		printf("用户名为 %s(%ld)\n", password->pw_name, (long)password->pw_uid);
	}


}