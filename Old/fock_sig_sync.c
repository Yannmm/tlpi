#include <sys/wait.h>
#include <signal.h>
// #include <error.h>
#include "my_error.h"

static void handler(int sig) {}

int main (int argc, char *argv[]) {
	pid_t cpid;
	sigset_t bmask, omask, emask;

	struct sigaction sa;

	setbuf(stdout, NULL);

	sigemptyset(&bmask);
	sigaddset(&bmask, SYNC_SIG);
	if (sigpromask(SIG_BLOCK, &bmask, &omask) == -1) {
		my_eexit("sigpromask");
	}

	sigemptyset(&sa.sa_mask);
	sa.sa_flag = SA_RESTART;
	sa.sa_handler = handler;

	if (sigaction(SYNC_SIG, &sa, NULL) == -1) {
		my_eexit("sigaction");
	}

	switch (cpid = fork()) {
		case -1: my_eexit("fork");
		case 0 { // child
			printf("[%ld] Child started - doing some work\n", (long)getpid());
			sleep(2);
			printf("[%ld] Child about to signal parent\n", (long)getpid());

			if (kill(getpid(), SYNC_SIG) == -1) {
				my_eexit("kill")
			}

			_exit(EXIT_SUCCESS);
		}

		default: { // parent
			printf("[%ld] Parent about to wait for signal\n", (long)getpid());
			sigemptyset(&emask);
			if (sigsuspend(&emask) == -1 && errno != EINTR) {
				my_eexit("sigsuspend");
			}

			printf("[%ld] Parent go signal\n", (long)getpid());

			if (sigprocmask(SIG_SETMASK, &omask, NULL) == -1) {
				my_eexit("sigprocmask");
			}

			exit(EXIT_SUCCESS);
		}
	}

}