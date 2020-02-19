// #define _BSD_SOURCE
#include "../tlpi.h"

#define MAX_ALLOCS 1000000

int main(int argc, char const *argv[])
{

	puts("这是一个断点");
	char *ptr[MAX_ALLOCS];
	int fstep, fmin, fmax, bsize, anumber, j;

	printf("\n");

	if (argc < 3 || strcmp(argv[1], "--help") == 0) {
		usage_error("%s num-allocs block-size [step [min [max]]]\n", argv[0]);
	}

	anumber = get_int(argv[1], GN_GT_0 | GN_ANY_BASE, "number-allocs");
	if (anumber > MAX_ALLOCS) {
		cmdl_error("num-allocs > %d\n", MAX_ALLOCS);
	}

	bsize = get_int(argv[2], GN_GT_0 | GN_ANY_BASE, "block-size");
	fstep = (argc > 3) ? get_int(argv[3], GN_GT_0, "step") : 1;
	fmin = (argc > 4) ? get_int(argv[4], GN_GT_0, "min") : 1;
	fmax = (argc > 5) ? get_int(argv[5], GN_GT_0, "max") : anumber;

	if (fmax > anumber) {
		cmdl_error("free-max > num-allocs\n");
	}

	printf("Initial program break:		%10p\n", sbrk(0));

	printf("Allocating %d * %d = %d bytes\n", anumber, bsize, anumber * bsize);

	for (j = 0; j < anumber; j++) {
		ptr[j] = malloc(bsize);
		printf("✨ sbrk:		%10p\n", sbrk(0));
		if (ptr[j] == NULL) {
			error_exit("malloc");
		}
	}

	printf("Program break is now:		%10p\n", sbrk(0));

	printf("Freeing blocks from %d to %d in steps of %d\n", fmin, fmax, fstep);

	for (j = fmin - 1; j < fmax; j += fstep) {
		free(ptr[j]);
	}

	printf("after free(), program break is: %10p\n", sbrk(0));

	return 0;
}