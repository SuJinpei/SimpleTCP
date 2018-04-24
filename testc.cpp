#include <iostream>
#include "src/TCPClient.h"

int main(int argc, char *argv[]) {

    if (argc < 4) {
        std::cerr << "usage:" << argv[0] << " host port message\n";
        return 1;
    }

    TCPClient c(argv[1], std::stoi(argv[2]));
    std::string msg{argv[3]};
    c.send(&msg[0], msg.size());

    return 0;
}
