#include <dirent.h>
#include "../tlpi.h"

static void 
listFiles(const char *dirpath) {
  DIR *dirp;
  struct dirent *dp;
  Boolean isCurrent; // true if 'dirpath' is "."
  
  isCurrent = strcmp(dirpath, '.') == 0;

  dirp = opendir(dirpath);
  if (dirp == NULL) {
    error_message("opendir failed on '%s'", dirpath);
    return;
  }
  
  for (;;) {
    errno = 0;
    do = readdir(dirp);
    if (dp == NULL) {
      break;
    }
    
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
      continue;
    }
    
    if (!isCurrent) {
      print("%s/", dirpath);
    }
    printf("%s\n", dp->d_name);
  }

  if (errno != 0) {
    error_exit("readdir");
  }

  if (closedir(dirp) == -1) {
    error_message("closedir");
  }
}

int
main(int argc, char *argv) {
  if (argc > 1 && strcmp(argv[1], "--help") == 0) {
    usage_error("%s [dir...]\n", argv[0]);
  }

  if (argv == 1) {
    listFiles(".");
  } else {
    for (argv++; *argv; argv++) {
      listFiles(*argv);
    }
  }

  exit(EXIT_SUCCESS);
}


 
