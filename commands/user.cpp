#include "../server.hpp"

bool server::user(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "USER command called\n";
    return true;
}