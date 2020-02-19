#include <sys/times.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void ptshow(const char *msg) {
	struct tms t;
	clock_t ctime;
	static long cticks = 0;

	if (msg != NULL) {
		printf("%s", msg);
	}

	if (cticks == 0) { // fetch clock ticks
		cticks = sysconf(_SC_CLK_TCK);
		if (cticks == -1) {
			exit(1);
		}
	}

	ctime = clock();
	if (ctime == -1) {
		exit(1);
	}


	printf("		clock() returns: %ld clocks-per-sec (%.8f secs)\n", (long)ctime, (double)ctime / CLOCKS_PER_SEC);

	if (times(&t) == -1) {
		exit(1);
	}

	printf("		times() yields: user CPU=%.2f; system CPU: %.2f\n", (double)t.tms_utime / cticks, (double)t.tms_stime / cticks);
}

int main(int argc, char *argv[]) {
	int ccount, j;

	printf("CLOCKS_PER_SEC=%ld	sysconf(_SC_CLK_TCK)=%ld\n\n", (long)CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));

	ptshow("At program start:\n");

	// ccount = (argc > 1) ? getInt
	ccount = 10000000;
	for (j = 0; j < ccount; j++) {
		(void)getppid();
	}

	ptshow("After getppid() loop:\n");
	exit(0);
}