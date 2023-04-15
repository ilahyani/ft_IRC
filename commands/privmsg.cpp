#include "../server.hpp"

bool server::privmsg(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "PRIVMSG command called\n";
    return true;
}