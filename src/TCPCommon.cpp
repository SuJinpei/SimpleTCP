#include <iostream>
#include "TCPCommon.h"

TCPConnection::~TCPConnection() {
    if (fd) {
        shutdown(fd, SHUT_RDWR);
    }
}

size_t TCPConnection::send(const void* buf, size_t len) {
    size_t ret = ::send(fd, buf, len, 0);
    if (ret < 0) perror("ERROR send");
    return ret;
}

size_t TCPConnection::recv(void* buf, size_t len) {
    size_t ret = ::recv(fd, buf, len, 0);
    if (ret < 0) perror("ERROR recv");
    return ret;
}
