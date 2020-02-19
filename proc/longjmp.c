#include <setjmp.h>
#include "../tlpi.h"

static jmp_buf env;

static void f2() {
	longjmp(env, 2);
}

static void f1(int argc) {
	if (argc == 1) {
		longjmp(env, 1);
	}
	f2();
}

int main(int argc, char const *argv[])
{
	switch (setjmp(env)) {
		case 0:
		printf("calling f1() after intial setjmp()\n");
		f1(argc);
		break;

		case 1:
		printf("we just jump back from f1()\n");
		break;

		case 2:
		printf("back from f2()\n");
		break;
	}
	return 0;
}