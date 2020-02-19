#define _BSD_SOURCE
#define _XOPEN_SOURCE
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <errno.h>
// #include <shadow.h>
#include "../tlpi.h"

struct spwd {
	char *sp_pwdp;
};

struct spwd *getspnam(const char *name) {
	struct spwd *s = malloc(sizeof(struct spwd));
	s->sp_pwdp = "123456";
	return s;
}

int main(int argc, char const *argv[])
{
	char *username, *password, *encrypted, *p;
	struct passwd *pwd;
	struct spwd *spwd;
	Boolean authed;
	size_t length;
	long lnmax;

	lnmax = sysconf(_SC_LOGIN_NAME_MAX);
	if (lnmax == -1) {
		lnmax = 256;
	}

	username = malloc(lnmax);
	if (username == NULL) {
		error_exit("malloc");
	}

	printf("Use Name: ");
	fflush(stdout);
	if (fgets(username, lnmax, stdin) == NULL) {
		exit(EXIT_FAILURE);
	}

	length = strlen(username);
	if (username[length - 1] == '\n') {
		username[length - 1] = '\0';
	}

	pwd = getpwnam(username);
	if (pwd == NULL) {
		fatal("couldn't get password record.");
	}

	spwd = getspnam(username);
	if (spwd == NULL && errno == EACCES) {
		fatal("no permission to read shadow passsword file.");
	}

	if (spwd != NULL) {
		pwd->pw_passwd = spwd->sp_pwdp;
	}

	password = getpass("Password: ");

	encrypted = crypt(password, pwd->pw_passwd);

	for (p = password; *p != '\0';) {
		*p++ = '\0';
	}

	if (encrypted == NULL) {
		error_exit("crypt");
	}

	authed = strcmp(encrypted, pwd->pw_passwd) == 0;
	printf("encrypted -> %s\n", encrypted);
	if (!authed) {
		printf("Incorrect password\n");
		exit(EXIT_FAILURE);
	}

	printf("Successfully authenticated: UID=%ld\n", (long)pwd->pw_uid);

	exit(EXIT_SUCCESS);

	return 0;
}