#pragma once
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class TCPConnection {
public:
    TCPConnection(){};
    ~TCPConnection();
    size_t send(const void *buf, size_t len);
    size_t recv(void *buf, size_t len);

    sockaddr_in peer_addr;
    socklen_t addr_len;
    int fd = 0;
};

