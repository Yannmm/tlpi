#include "my_error.h"

void ym_perror(void) {
	puts("很明显这是错误信息\n");
}

void my_eexit(char *s) {
	printf("Error exit for %s...\n", s);
}