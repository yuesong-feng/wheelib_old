#include "src/net/net.h"

#include <sys/socket.h>

sock *sock_init(){
    socket *skt = (socket *)malloc(sizeof(sock));
    int sock_fd = socket();
    skt->fd = sock_fd;
}

void sock_free(socket *skt){
    free(skt);
}