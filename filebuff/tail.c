#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

#ifndef BUF_SIZE
#define BUF_SIZE (1024 * 5)
#endif

#define DEFAULT_NUMBER_LINES 10

static int number_lines = DEFAULT_NUMBER_LINES;
static char *filename = NULL;
static char buffer[BUF_SIZE];

void print_usage(int argc, char **argv) {
	fprintf(stderr, "Usage: %s [-n lines] <file>\n", argv[0]);
}

int parse_options(int argc, char **argv) {
	int c;
	while ((c = getopt(argc, argv, "n:") != -1) {
		switch (c) {
			case 'n':
			number_lines = atoi(optarg);
			break;
		}
	}
}