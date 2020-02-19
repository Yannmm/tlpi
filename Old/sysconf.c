#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

static void printsysc(const char *msg, int name) {
	long limit;
	errno = 0;

	limit = sysconf(name);
	if (limit != -1) { // 成功
		printf("%s %ld\n", msg, limit);
	} else {
		if (errno == 0) { // 不确定
			printf("%s (indeterminate)\n", msg);
		} else { // 错误
			printf("sysconf %s", msg);
			exit(1);
		}
	}
}

int main(int argc, char *argv[]) {
	printsysc("_SC_ARG_MAX:		", _SC_ARG_MAX);
	printsysc("_SC_LOGIN_NAME_MAX:		", _SC_LOGIN_NAME_MAX);
	printsysc("_SC_OPEN_MAX:		", _SC_OPEN_MAX);
	printsysc("_SC_NGROUPS_MAX:		", _SC_NGROUPS_MAX);
	printsysc("_SC_PAGE_SIZE:		", _SC_PAGE_SIZE);
	printsysc("_SC_RTSIG_MAX:		", _SC_RTSIG_MAX);

	return 0;
}