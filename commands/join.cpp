#include "../server.hpp"

bool server::join(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "JOIN command called\n";
    return true;
}