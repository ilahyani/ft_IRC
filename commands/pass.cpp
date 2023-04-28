#include "../server.hpp"

void server::pass(std::vector<std::string> params, std::map<int, client>::iterator client) {
    if (params.size() == 2 && params[1] == server::getPasswd())
    {
        client->second.loggedIn = true;
        std::cout << "Success !\n";
    }
    else 
        std::cout << "Wrong password, try again !\n";
}