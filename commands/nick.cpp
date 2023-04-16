#include "../server.hpp"

void server::nick(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "NICK command called\n";
}