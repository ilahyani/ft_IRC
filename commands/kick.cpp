#include "../server.hpp"

bool server::kick(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "KCIK command called\n";
    return true;
}