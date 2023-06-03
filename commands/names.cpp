#include "../server.hpp"

std::string server::getVisibleClients(Channels *ch)
{
    std::string str;
    std::vector<std::pair<client, ROLE> >::iterator clients = ch->getMembers().end();
    
    do
    {
        if (ch->getMembers().begin() != clients)
            clients--;
        else
            break;

        if (_connectedClients[clients->first.getsocket()].isInvisible == false)
        {
            if (clients->second == OPERATOR)
                str += ("@" + clients->first.getNickname() + " ");
            else
                str += (clients->first.getNickname() + " ");
        }
        
    } while (ch->getMembers().begin() != clients);
    return str;
}

void server::names(std::vector<std::string> params, std::map<int, client>::iterator client) {

    if (params.size() < 2)
    {
        client->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }
    Channels *ch = getChannel(params[1]);
    if (!ch)
        return ;
        
    if (ch && checkUserIsInChannel(client->first, ch))
    {
        client->second.ServertoClientPrefix(RPL_NAMREPLY(client->second.getNickname(), ch->getName(), getClientsChannel(ch)));
        client->second.ServertoClientPrefix(RPL_ENDOFNAMES(client->second.getNickname(), ch->getName()));
        return ;
    }
    else if (ch && !checkUserIsInChannel(client->first, ch))
    {
        client->second.ServertoClientPrefix(RPL_NAMREPLY(client->second.getNickname(), ch->getName(), getVisibleClients(ch)));
        client->second.ServertoClientPrefix(RPL_ENDOFNAMES(client->second.getNickname(), ch->getName()));
        return ;
    }
    client->second.ServertoClientPrefix(RPL_NAMREPLY(client->second.getNickname(), ch->getName(), ""));
    client->second.ServertoClientPrefix(RPL_ENDOFNAMES(client->second.getNickname(), ch->getName()));
    return ;
}