#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int nfds = 10;
  struct pollfd *fds;
  fds = (struct pollfd *)malloc(sizeof(struct pollfd) * nfds);
  memset(fds, 0, sizeof(struct pollfd) * nfds);
  fds[0].fd = 0;
  fds[0].events = POLL_IN;

  while (1) {
    int res = poll(fds, nfds, -1);
    printf("%d\n", res);
    for (int i = 0; i < res; ++i) {
      printf("%d\n", fds[i].fd);
    }
    fflush(stdin);
  }

  free(fds);
  return 0;
}