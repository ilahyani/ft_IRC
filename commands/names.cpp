#include "../server.hpp"

void server::names(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "NAMES command called ===> \n";
}