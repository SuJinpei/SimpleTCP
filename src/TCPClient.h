#pragma once
#include <string>
#include "TCPCommon.h"

class TCPClient {
public:
    TCPClient(const std::string& ipAddr, unsigned short port);
    size_t send(const void *buf, size_t len);
    size_t recv(void *buf, size_t len);

private:
    TCPConnection c;
};
