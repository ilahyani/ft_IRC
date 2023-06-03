#include "../server.hpp"

void server::pong(std::vector<std::string> params, std::map<int, client>::iterator client) {

    if (params[1].empty())
    {
        client->second.ServertoClientPrefix(ERR_NOORIGIN(client->second.getNickname()));
        return ;
    }
    else if (params[1].compare(_hostAdr))
    {
        client->second.ServertoClientPrefix(ERR_NOSUCHSERVER(client->second.getNickname(), params[1]));
        return ;
    }
}