#include "../server.hpp"

void server::notice(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "NOTICE command called\n";
}