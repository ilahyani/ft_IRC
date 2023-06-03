#include "../server.hpp"

void server::privmsg(std::vector<std::string> params, std::map<int, client>::iterator cl) {

    if (params.size() < 2)
    {
        cl->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(cl->second.getNickname()));
        return ;
    }

    if (params.size() < 3)
    {
        cl->second.ServertoClientPrefix(ERR_NOTEXTTOSEND(cl->second.getNickname()));
        return ;
    }

    if (params[1][0] == '#' && params[1].size() > 1)
    {
        Channels *ch = getChannel(params[1]);
        if (!ch)
        {
            cl->second.ServertoClientPrefix(ERR_NOSUCHCHANNEL(cl->second.getNickname(), params[1]));
            return ;
        }
        if (!checkUserIsInChannel(cl->second, ch))
        {
            cl->second.ServertoClientPrefix(ERR_NOTONCHANNEL(cl->second.getNickname(), ch->getName()));
            return ;
        }
        send_msg_to_clients_who_in_channel(ch, cl->second, "PRIVMSG " + ch->getName() + " :" + params[2]);
    }
    else
    {
        client *receiver = get_client(params[1]);
        if (!receiver)
        {
            cl->second.ServertoClientPrefix(ERR_NOSUCHNICK(cl->second.getNickname(), params[1]));
            return ;
        }
        sendToClientById(receiver->getsocket(), cl->second, "PRIVMSG " + receiver->getNickname() + " :" + params[2]);
    }
}