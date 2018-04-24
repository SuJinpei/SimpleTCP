#include <iostream>
#include <string>
#include "src/TCPServer.h"

class RequestHander: public BaseRequestHandler {
public:
    void handle() override {
        char buf[1024];
        while(conn.recv(buf, sizeof(buf)) > 0) {
            std::cout << buf << std::endl;
            if (buf[0] == 'e' && buf[1] == 'n' && buf[2] == 'd') break;
        }
        std::cout << "connection finished\n";
    }
};

class RequestHandlerFactory: public BaseRequestHandlerFactory {
public:
    RequestHander *createHandler() override {
        return new RequestHander();
    }
};

int main(int argc, char *argv[]) {

    if (argc < 3) {
        std::cerr << "usage:" << argv[0] << " host port\n";
        return 1;
    }

    TCPServer s(argv[1], std::stoi(argv[2]), new RequestHandlerFactory);
    std::cout << "server started\n";
    s.serve_forever();

    return 0;
}
