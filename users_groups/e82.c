#include "../tlpi.h"
#include <sys/types.h>
#include <pwd.h>
#include <string.h>

struct passwd *
ym_getpwnam(const char *name) {
	struct passwd *next;
	int i;

	errno = 0;
	for (i = 0; ;i++) {
		next = getpwent();
		if (next == NULL) {
			if (errno == 0) {
				break;
			} else {
				error_exit("getpwent");
			}
		} else {
			if (strcmp(name, next->pw_name) == 0) {
				break;
			}
		}
	}

	endpwent();
	return next;
}

int main(int argc, char const *argv[])
{
	struct passwd *me;

	me = ym_getpwnam("kio");

	if (me != NULL) {
		printf("This is me -> %s, uid -> %s", me->pw_name, me->pw_passwd);
	} else {
		puts("You didn't find me");
	}


	return 0;
}