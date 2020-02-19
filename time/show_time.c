#include <time.h>
#include <locale.h>
#include "../tlpi.h"

#define BUF_SIZE 200

int main(int argc, char *argv[]) {
	time_t t;
	struct tm *loc;
	char buffer[BUF_SIZE];
	
	if (setlocale(LC_ALL, "") == NULL) {
		error_exit("setlocale");
	}
	
	t = time(NULL);
	
	printf("ctime() of time() value is:	%s", ctime(&t));
	
	loc = localtime(&t);
	
	if (loc == NULL) {.            
		error_exit("localtime");
	}
	
	printf("asctime() of local time is:	%s", asctime(loc));
	
	if (strftime(buffer, BUF_SIZE, "%A %d %B %Y, %H:%M:%S %Z", loc) == 0) {
		fatal("strftime returned 0");
	}
	
	printf("strftime() of local time is: %s\n", buffer);
	
	return 0;
}