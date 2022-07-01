#define _NET_H_
#define _NET_H_

typedef enum sock_status {INIT, CONNECTED, CLOSE} sock_status;
typedef struct sock {
  int fd;
    sock_status status;
} sock;

sock *sock_init();

void sock_free(sock *skt);

#endif
