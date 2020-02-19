#define _XOPEN_SOURCE
#include <time.h>
#include <locale.h>
#include "../tlpi.h"

#define SBUF_SIZE 1000

int main(int argc, char const *argv[])
{
	struct tm tm;
	char sbuffer[SBUF_SIZE];
	char *ofmt;

	if (argc < 3 || strcmp(argv[1], "--help") == 0) {
		usage_error("%s input-date-time in-format [out-format]\n", argv[0]);
	}

	if (setlocale(LC_ALL, "") == NULL) {
		error_exit("setlocale"); // use locale settings in conversions
	}

	memset(&tm, 0, sizeof(struct tm));
	if (strptime(argv[1], argv[2], &tm) == NULL) {
		fatal("strptime");
	}

	tm.tm_isdst = -1;

	printf("calendar time (seconds since Epoch): %ld\n", (long)mktime(&tm));

	ofmt = (argc > 3) ? (char *)argv[3] : "%H:%M:%S %A, %d %B %Y %Z";
	if (strftime(sbuffer, SBUF_SIZE, ofmt, &tm) == 0) {
		fatal("strftime returned 0");
	}
	printf("strftime() yields: %s\n", sbuffer);

	return 0;
}