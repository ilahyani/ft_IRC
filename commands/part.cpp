#include "../server.hpp"

bool server::part(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "PART command called\n";
    return true;
}