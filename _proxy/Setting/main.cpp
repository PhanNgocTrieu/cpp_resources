#include <iostream>
#include "../Sockets/SocketService.hpp"
int main(int argc, char **argv) {
    std::cout << "Welcome to setting Application" << std::endl;
    SocketService s(false, argc, argv);
    return 0;
}