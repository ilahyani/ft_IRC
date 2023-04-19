#include "../server.hpp"

void server::mod(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "MOD command called\n";
}