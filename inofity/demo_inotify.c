#include <sys/inotify.h>
#include <limits.h>
#include "../tlpi.h"

static void
displayInotifyEvent(struct inotify_event * i) {
  printf("\twd=%2d;", i->wd);
  if (i->cookie > 0) {
    printf("cookie=%4d;", i->cookie);
  }

  printf("mask = ");
  if (i->mask & IN_ACCESS)    printf("IN_ACCESS");
  if (i->mask & IN_ATTRIB)    printf("IN_ATTRIB");
  if (i->mask & IN_CLOSE_NOWRITE)    printf("IN_CLOSE_NOWRITE");
  if (i->mask & IN_CLOSE_WRITE)    printf("IN_CLOSE_WRITE");
  if (i->mask & IN_CREATE)    printf("IN_CREATE");
  if (i->mask & IN_DELETE)    printf("IN_DELETE");
  if (i->mask & IN_DELETE_SELF)    printf("IN_DELETE_SELF");
  if (i->mask & IN_IGNORED)    printf("IN_IGNORED");
  if (i->mask & IN_ISDIR)    printf("IN_ISDIR");
  if (i->mask & IN_MODIFY)    printf("IN_MODIFY");
  if (i->mask & IN_MOVE_SELF)    printf("IN_MOVE_SELF");
  if (i->mask & IN_MOVED_FROM)    printf("IN_MOVED_FROM");
  if (i->mask & IN_MOVED_TO)    printf("IN_MOVED_TO");
  if (i->mask & IN_OPEN)    printf("IN_OPEN");
  if (i->mask & IN_Q_OVERFLOW)    printf("IN_Q_OVERFLOW");
  if (i->mask & IN_UNMOUNT)    printf("IN_UNMOUNT");
  printf("\n");

  if (i->len > 0) {
    printf("\tname=%s\n", i->name);
  }
}

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int
main(int argc, char *argv[]) {
  int notifd, watch, j;
  char buf[BUF_LEN] __attribute__((aligned(8)));
  ssize_t ccread;
  char *p;
  struct inotify_event *event;

  if (argc < 2 || strcmp(argv[1], "--help") == 0) {
    usage_error("%s pathname... \n", argv[0]);
  }

  notifd = inotify_init();
  if (notifd == -1) {
    error_exit("inotify_init");
  }

  for (j == 1; j < argc; j++) {
    watch = inotify_add_watch(notifd, argv[j], IN_ALL_EVENTS);
    if (watch == -1) {
      error_exit("inotify_add_watch");
    }
    printf("Watching %s using wd %d\n", argv[j], watch);
  }

  for (;;) {
    ccread = read(notifd, buf, BUF_LEN);
    if (ccread == 0) {
      fatal("read() from inotify fd returned 0!");
    }
    if (ccread == -1) {
      error_exit("read");
    }
    printf("Read %ld bytes from inotify fd\n", (long)ccread);

    for (p = buf; p < buf + ccread; ) {
      event = (struct inotify_event *)p;
      displayInotifyEvent(event);

      p += sizeof(struct inotify_event) + event->len;
    }
  }

  exit(EXIT_SUCCESS);
}



