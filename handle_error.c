#include <stdarg.h>
#include "handle_error.h"
#include "tlpi.h"
#include "ename.c.inc"

#ifdef __GNUC__
__attribute__((__noreturn__))
#endif

static void terminate(Boolean flag) {
	char *s;
	s = getenv("EF_DUMPCORE");

	if (s != NULL && *s!= '\0') {
		abort();
	} else if (flag) {
		exit(EXIT_FAILURE);
	} else {
		_exit(EXIT_FAILURE);
	}
}

static void output_error(Boolean erelated, int error, Boolean flush, const char *format, va_list ap) {
	#ifndef BUF_SIZE
	#define BUF_SIZE 500
	#endif
	char buffer[BUF_SIZE], usermsg[BUF_SIZE], errmsg[BUF_SIZE];

		vsnprintf(usermsg, BUF_SIZE, format, ap);

		if (erelated) {
			snprintf(errmsg, BUF_SIZE, " [%s %s]", (error > 0 && error <= MAX_ENAME) ? ename[error] : "?UNKNOWN?", strerror(error));
		} else {
			snprintf(errmsg, BUF_SIZE, ":");
		}

		snprintf(buffer, BUF_SIZE, "ERROR%s %s\n", errmsg, usermsg);

		if (flush) {
			fflush(stdout);
		}
		fputs(buffer, stderr);
		fflush(stderr);
}

void error_message(const char *format, ...) {
	va_list ap;
	int serror;
	serror = errno;
	va_start(ap, format);
	output_error(true, errno, true, format, ap);
	va_end(ap);

	errno = serror;
}

void error_exit(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	output_error(true, errno, true, format, ap);
	va_end(ap);
	terminate(true);
}

void error__exit(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	output_error(true, errno, false, format, ap);
	va_end(ap);
	terminate(false);
}

void error_exit_en(int en, const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	output_error(true, en, false, format, ap);
	va_end(ap);
	terminate(true);
}

void fatal(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	output_error(false, 0, true, format, ap);
	va_end(ap);
	terminate(true);
}

void usage_error(const char *format, ...) {
	va_list ap;
	fflush(stdout); // flush any pending stdout
	fprintf(stderr, "Usage: ");
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	fflush(stderr);
	exit(EXIT_FAILURE);
}

void cmdl_error(const char *format, ...) {
	va_list ap;
	fflush(stdout);
	fprintf(stderr, "Command-line usage error: ");
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);

	fflush(stderr);
	exit(EXIT_FAILURE);
}
