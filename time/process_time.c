#include <sys/times.h>
#include <time.h>
#include "tlpi.h"

static void display_ptimes(const char *msg) {
	struct tms t;
	clock_t clocktime;
	static long clockticks = 0;
	
	if (msg != NULL) {
		printf("%s", msg);
	}
	
	if (clockticks == 0) {
		clockticks = sysconf(_SC_CLK_TCK);
		if (clockticks == -1) {
			error_exit("sysconf");
		}
	}
	
	clocktime = clock();
	if (clocktime == -1) {
		error_exit("clock()");
	}
	
	printf("	clock() reutrns: %ld; clocks-per-sec: (%.2f)\n", (long)clocktime, (double)clocktime / CLOCKS_PER_SEC);
	
	if (times(&t) == -1) {
		error_exit("times");
	}
	printf("	times() yields: user cpu=%.2f; system cpu=%.2f\n", (double)t.tms_utime / clockticks, (double)t.tms_stime / clockticks);
}

int main(int argc, char *argv[]) {
	int ncalls, j;
	
	printf("CLOCKS_PER_SEC=%ld sysconf(_SC_CLK_TCK)=%ld\n\n", (long)CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));
	display_ptimes("At program start:\n");
	
	ncalls = (argc > 1) ? get_int(argv[1], GN_GT_0, "num-calls") : 10000000;
	for (j = 0; j < ncalls : j++) {
		(void)getppid();
	}
	
	display_ptimes("After getppid() loop:\n");
	
	return -0;
}