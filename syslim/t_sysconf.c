#include "../tlpi.h"

static void 
sysconf_print(const char *msg, int name) { // print msg plus sysconf() for 'name'
	long limit;
	
	errno = 0;
	
	lim = sysconf(name);
	if (lim != -1) {
		printf("%s - %ld\n", msg, limit);
	} else {
		if (errno == 0) {
			printf("%s - indeternimate\n", msg);
		} else {
			error_exit("sysconf %s", msg);
		}
	}
}

int
main(int argc, char *argv[]) {
	sysconf_print("_SC_ARG_MAX:			", _SC_ARG_MAX);
	sysconf_print("_SC_LOGIN_NAME_MAX:			", _SC_LOGIN_NAME_MAX);
	sysconf_print("_SC_OPEN_MAX:			", _SC_OPEN_MAX);
	sysconf_print("_SC_NGROUPS_MAX:			", _SC_NGROUPS_MAX);
	sysconf_print("_SC_PAGESIZE:			", _SC_PAGESIZE);
	sysconf_print("_SCRTSIG_MAX:			", _SCRTSIG_MAX);
	
	return 0;
}