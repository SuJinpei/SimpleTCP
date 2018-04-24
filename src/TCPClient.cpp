#include "TCPClient.h"
#include <iostream>

TCPClient::TCPClient(const std::string& ipAddr, unsigned short port) {
    std::cout << "Connect to:" << ipAddr << ':' << port << std::endl;
    c.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (c.fd < 0) perror("ERROR socket");
    std::cout << "socket success\n";
    c.peer_addr.sin_family = AF_INET;
    c.peer_addr.sin_addr.s_addr = inet_addr(ipAddr.c_str());
    c.peer_addr.sin_port = htons(port);
    if(::connect(c.fd, (sockaddr*)&c.peer_addr, sizeof(c.peer_addr)) < 0) perror("connect");
    std::cout << "client initialized\n";
}

size_t TCPClient::send(const void *buf, size_t len) {
    return c.send(buf, len);
}

size_t TCPClient::recv(void *buf, size_t len) {
    return c.recv(buf, len);
}
