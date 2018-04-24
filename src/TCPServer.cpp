#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include "TCPServer.h"

TCPServer::TCPServer(std::string ipAddr, unsigned short port, BaseRequestHandlerFactory *pf)
    :hostIP{ipAddr}, portNo{port}, hanlerFactory{pf}{
    std::cout << "Server:" << ipAddr << ':' << port << std::endl;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd<0) perror("ERROR socket");
    srvr_addr.sin_family = AF_INET;
    srvr_addr.sin_addr.s_addr =inet_addr(ipAddr.c_str());
    srvr_addr.sin_port = htons(port);
    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) perror("ERROR reuse address");
    if(bind(sockfd, (sockaddr*)&srvr_addr, sizeof(srvr_addr)) < 0) perror("ERROR bind");
    if(listen(sockfd, 10) < 0) perror("ERROR listen");
}

TCPServer::~TCPServer() {
    if (sockfd) {
        shutdown(sockfd, SHUT_RDWR);
    }
}

void TCPServer::serve_forever() {
    std::cout << "server started:\n";
    std::vector<std::thread> tv;
    while (true) {
        std::shared_ptr<BaseRequestHandler> pHander{hanlerFactory->createHandler()};
        pHander->conn.fd = ::accept(sockfd, (sockaddr*)&(pHander->conn.peer_addr), &(pHander->conn.addr_len));
        std::cout << "client connect\n";
        if (pHander->conn.fd < 0) break;
        tv.push_back(std::thread{[pHander]{pHander->handle();}});
    }

    for (auto& t : tv) t.join();
}
