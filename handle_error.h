#ifndef HANDLE_ERROR_H
#define HANDLE_ERROR_H

void error_message(const char *format, ...);

#ifdef __GNUC__

#define NORETURN __attribute__((__noreturn__))
#else
#define NORETURN
#endif

void error_exit(const char *format, ...) NORETURN;
void error__exit(const char *format, ...) NORETURN;
void error_exit_en(int enumber, const char *format, ...) NORETURN;
void fatal(const char *format, ...) NORETURN;
void usage_error(const char *format, ...) NORETURN;
void cmdl_error(const char *format, ...) NORETURN;
#endif

