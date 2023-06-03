#include "server.hpp"

int main(int ac, char **av) {
    server  serv;
    int     port;

    if (ac != 3)
        return std::cerr << "Wrong arguments. Try Again!\n", 1;
    port = atoi(av[1]);
    if (port < 1024 || port > 65535)
        return std::cerr << "Invalid port number. Port is either reserved for system services or do not exist\n", 1;
    serv = server(port, av[2]);
    if (!serv.startServ())
        return 1;
    return 0;
}