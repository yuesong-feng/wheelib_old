#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handle_sigint(int sig) {
	printf("int %d\n", sig);
	exit(0);
}

int main() {
	signal(SIGINT, handle_sigint);
	while(1) {}
	return 0;
}
