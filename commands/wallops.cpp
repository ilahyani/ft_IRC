#include "../server.hpp"

void server::wallops(std::vector<std::string> params, std::map<int, client>::iterator cl) {
    
    if (params.size() < 2)
    {
        cl->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(cl->second.getNickname()));
        return ;
    }

    if (!cl->second.isOpreator)
    {
        cl->second.ServertoClientPrefix(ERR_NOPRIVILEGES(cl->second.getNickname()));
        return ;
    }

    std::map<int, client>::iterator it = _connectedClients.begin();
    while (it != _connectedClients.end())
    {
        if (it->second.wallops && it->second.getsocket() != cl->second.getsocket())
            sendToClientById(it->second.getsocket(), cl->second, "NOTICE " + it->second.getNickname() + " :" + params[1]);
        it++;
    }
}