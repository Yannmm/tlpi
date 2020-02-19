#include "my_error.h"
#include <unistd.h>
#include <string.h>

int main (int argc, char *argv[]) {
	char *args[10];
	char *env[] = {"GREET=salut", "BYE=adieu", NULL};

	args[0] = strrchr(argv[1], '/');
	if (args[0] != NULL) {
		args[0]++;
	} else {
		args[0] = argv[1];
	}

	args[1] = "helo world";
	args[2] = "goodbye";
	args[3] = NULL;

	execve(argv[1], args, env);
	my_eexit("execve");
}