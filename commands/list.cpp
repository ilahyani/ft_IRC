#include "../server.hpp"

void server::list(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "LIST command called\n";
}