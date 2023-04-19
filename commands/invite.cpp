#include "../server.hpp"

void server::invite(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "INVITE command called\n";
}