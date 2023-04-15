#include "../server.hpp"

bool server::nick(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "NICK command called\n";
    return true;
}