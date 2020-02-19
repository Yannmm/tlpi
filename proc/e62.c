#include <setjmp.h>
#include "../tlpi.h"

static jmp_buf env;

static void trampoline() {
	switch (setjmp(env)) {
		case 0:
		printf("calling f1() after intial setjmp()\n");
		break;
		case 1:
		printf("return from deadend()\n");
		break;
	}
}

int main(int argc, char const *argv[])
{
	trampoline();
	longjmp(env, 1);
	return 0;
}