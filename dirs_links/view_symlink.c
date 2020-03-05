#include <sys/stat.h>
#include <limits.h>
#include "../tlpi.h"

#define BUF_SIZE PATH_MAX

int
main(int argc, char *argv[]) {
  struct stat statbuf;
  char buf[BUF_SIZE];
  ssize_t nbytes;

  if (argc != 2 || strcmp(argv[1], "--help") == 0) {
    usage_error("%s pathname\n", argv[0]);
  }

  if (lstat(argv[1], &statbuf) == -1) {
    error_exit("lstat");
  }

  if (!S_ISLNK(statbuf.st_mode)) {
    fatal("%s is not a symbolic link", argv[1]);
  }

  nbytes = readlink(argv[1], buf, BUF_SIZE -1);
  if (nbytes == -1) {
    error_exit("readlink");
  }

  buf[nbytes] = '\0';
  printf("readlink: %s --> %s\n", argv[1], buf);

  if (realpath(argv[1], buf) == NULL) {
    error_exit("realpath");
  }
  printf("realpath: %s -->%s\n", argv[1], buf);

  exit(EXIT_SUCCESS);
}
