#include <stdio.h>
#include <pwd.h>
#include <ctype.h>
#include <shadow.h>

int main(int argc, char const *argv[])
{
	// struct passwd *pwentry;
	// while((pwentry = getpwent()) != NULL) {
	// 	printf("%-8s - %s - %5ld\n", pwentry->pw_name, pwentry->pw_passwd, (long)pwentry->pw_uid);
	// }

	struct spwd *pwe;
	while((pwe = getspent()) != NULL) {
		printf("%-8s - %s - %5ld\n", pwe->sp_namp, pwe->sp_pwdp, pwe->sp_lstchg);
	}

	return 0;
}