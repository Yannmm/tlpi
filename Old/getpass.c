#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char *password = getpass("plz neter password:");

	printf("密码是 %s\n", password);

	char *encrypted = crypt(password, "33");

	printf("加密后 %s\n", encrypted);
}