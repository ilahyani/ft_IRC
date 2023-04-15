#include "../server.hpp"

bool server::pass(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "PASS command called\n";
    return true;
}