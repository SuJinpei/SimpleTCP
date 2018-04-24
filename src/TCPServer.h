#pragma once
#include <cstdio>
#include <error.h>
#include <string>
#include "TCPCommon.h"

class BaseRequestHandler {
public:
    virtual void handle() = 0;
    TCPConnection conn;
};

class BaseRequestHandlerFactory {
public:
    virtual BaseRequestHandler* createHandler() = 0;
};

class TCPServer {
public:
    TCPServer(std::string ipAddr, unsigned short port, BaseRequestHandlerFactory *pf);
    ~TCPServer();

    void serve_forever();

private:
    int sockfd;
    std::string hostIP;

    sockaddr_in srvr_addr;
    unsigned short portNo;
    BaseRequestHandlerFactory *hanlerFactory;
};
