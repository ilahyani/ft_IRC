#include "../server.hpp"

void server::pass(std::vector<std::string> params, std::map<int, client>::iterator client) {
    if (!client->second.loggedIn)
    {
        if (params.size() < 2)
        {
            client->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(client->second.getNickname()));
            return ;
        }
        if (params[1] != server::getPasswd() || params.size() != 2)
        {
            client->second.ServertoClientPrefix(ERR_PASSWDMISMATCH(client->second.getNickname()));
            return ;   
        }
        client->second.loggedIn = true;
    }
}