#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int ch;

	opterr = 0;
	printf("\n\n");
	printf("option:%d, opterr:%d\n", optind, opterr);
	puts("----------------------");
	while((ch = getopt(argc, argv, "ab:c:de::")) != -1) {
		printf("optind: %d ---> opt: %c\n", optind, (char)optopt);
		switch (ch) {
			case 'a': {
				printf("option -a\n\n");
				break;
			}
			case 'b': {
				printf("option -b\n\n");
				printf("-b has argument: %s\n\n", optarg);
				break;
			}
			case 'c': {
				printf("option -c\n\n");
				printf("-c has argument: %s\n\n", optarg);
				break;
			}
			case 'd': {
				printf("option -d\n\n");
				break;
			}
			case 'e': {
				printf("option -e\n\n");
				printf("-e has argument: %s\n\n", optarg);
				break;
			}
			case '?': {
				printf("unknown option: %c\n", (char)optopt);
				break;
			}
		}
	}

	return 0;
}
