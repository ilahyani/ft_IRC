#include "../server.hpp"

void server::part(std::vector<std::string> params, std::map<int, client>::iterator client) {

    if (params.size() < 2)
    {
        client->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }

    Channels *ch = getChannel(params[1]);
    if (!ch)
    {
        client->second.ServertoClientPrefix(ERR_NOSUCHCHANNEL(client->second.getNickname(), params[1]));
        return ;
    }

    if (!checkUserIsInChannel(client->second, ch))
    {
        client->second.ServertoClientPrefix(ERR_NOTONCHANNEL(client->second.getNickname(), params[1]));
        return ;
    }

    send_to_all_in_channel(ch, client->second, "PART " + ch->getName());
    ch->removeMember(client->second);
}