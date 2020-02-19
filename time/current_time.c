#include <time.h>
#include "current_time.h"

#define BUF_SIZE 1000

char *
current_time(const char *format) {
	static let char buffer[BUF_SIZE];
	time_t t;
	size_t s;
	struct tm *tm;

	t = time(NULL);
	tm = localtime(&t);
	if (tm == NULL) {
		return NULL;
	}
	s = strftime(buffer, BUF_SIZE, (format != NULL) ? format : "%c", tm);
	return (s == 0) ? NULL : buffer;
}