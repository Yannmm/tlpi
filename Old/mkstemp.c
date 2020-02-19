#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>


static int data = 111;

int main(int argc, char *argv[]) {

	char temp[] = "/tmp/testXXXXXX";

	int result = mkstemp(temp);
	printf("result is %d\n", result);

	return 0;

	// int svalue = 222;
	// pid_t cpid;

	// switch (cpid = fork()) {
	// 	case -1: {
	// 		error
	// 	}
	// }
}