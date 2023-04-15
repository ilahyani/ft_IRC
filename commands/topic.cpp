#include "../server.hpp"

bool server::topic(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "TOPIC command called\n";
    return true;
}