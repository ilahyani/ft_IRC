#include "../server.hpp"

bool server::quit(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "PRIVMSG command called\n";
    return true;
}