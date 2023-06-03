#include "../server.hpp"

std::string getIdle(std::time_t time)
{
    std::stringstream ss;
    ss << std::difftime(std::time(NULL), time);
    return ss.str();
}

void server::whois(std::vector<std::string> params, std::map<int, client>::iterator cl) {

    
    if (params.size() == 1)
    {
        cl->second.ServertoClientPrefix(ERR_NONICKNAMEGIVEN(cl->second.getNickname()));
        return ;
    }
    
    std::string users;
    users = params[1];
    
    size_t pos;
    size_t index = 0;
    std::string user;
    int sign = 1;
    std::string tmp;
    
    while (1337)
    {
        pos = users.find(',', index);
        user = users.substr(index, pos - index);
        index = pos + 1;
        
        client * c = get_client(user);
        if (c)
        {
            if (sign)
            {
                tmp = c->getNickname();
                sign = 0;
            }
            cl->second.ServertoClientPrefix(RPL_WHOISUSER(cl->second.getNickname(), user, c->getNickname(), c->getHostIp(), c->getRealname()));
            std::vector<Channels>::iterator it_ch = _Channels.begin();
            std::string channels;
            for (; it_ch != _Channels.end(); it_ch++)
            {
                std::vector<std::pair<client, ROLE> >::iterator it_cl = it_ch->getMembers().begin();
                while (it_cl != it_ch->getMembers().end())
                {
                    if (c->getsocket() == it_cl->first.getsocket())
                    {
                        if (it_cl->second == OPERATOR)
                            channels += "@" + it_ch->getName() + " ";
                        else
                            channels += it_ch->getName() + " ";
                    }
                    it_cl++;
                }
            }
            if (!channels.empty())
                cl->second.ServertoClientPrefix(RPL_WHOISCHANNELS(cl->second.getNickname(), c->getNickname(), channels));
            cl->second.ServertoClientPrefix(RPL_WHOISSERVER(cl->second.getNickname(), c->getNickname(), cl->second.getHostIp(), "ft_irc"));
            cl->second.ServertoClientPrefix(RPL_WHOISIDLE(cl->second.getNickname(), c->getNickname(), getIdle(cl->second._time), cl->second.getJoiningTime()));
        }
        else
            cl->second.ServertoClientPrefix(ERR_NOSUCHNICK(cl->second.getNickname(), user));
        if (pos == std::string::npos)
            break;
    }

    cl->second.ServertoClientPrefix(RPL_ENDOFWHOIS(cl->second.getNickname(), tmp));
}