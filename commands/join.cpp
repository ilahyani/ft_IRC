/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:08:28 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/28 19:30:01 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"
#include "../client.hpp"

bool check_channel_name(std::string channel)
{
    std::string invalidChars = " ,:;-?!&%\\/()[]{}\"'~^$#*";
    if (channel[0] != '#')
        return false;
    for (int i = 1; i < (int)channel.length(); i++)
    {
        if (invalidChars.find(channel[i]) != std::string::npos)
            return false;
    }
    return true;
}

std::string getClientsChannel(Channels *ch)
{
    std::string str;
    std::vector<std::pair<client, ROLE> > clients = ch->getMembers();

    int i = clients.size() - 1;
    while (i >= 0)
    {
        if (clients[i].second == OPERATOR)
            str += ("@" + clients[i].first.getNickname() + " ");
        else
            str += (clients[i].first.getNickname() + " ");
        i--;
    }
    return str;
}

void    print_infos_after_join(std::string clients_of_channel, client &client, Channels *channel)
{
    client.response("JOIN :" + channel->getName());
    if (!channel->geTopic().empty())
        client.responsefromServer(RPL_TOPIC(client.getNickname(), channel->getName(), channel->geTopic()));
    client.responsefromServer(RPL_NAMREPLY(client.getNickname(), channel->getName(), clients_of_channel));
    client.responsefromServer(RPL_ENDOFNAMES(client.getNickname(), channel->getName()));    
}

void server::join_to_channel(std::string channel, std::string key, client &cl)
{
    Channels *ch = getChannel(channel);
    
    if (ch != NULL && ch->getName() == channel)
    {
        if (!checkUserIsInChannel(cl, ch))
        {
            if ((int)ch->getMembers().size() == ch->getLimit())
            {
                cl.responsefromServer(ERR_CHANNELISFULL(cl.getNickname(), ch->getName()));
                return ;
            }
            if (ch->isProtected && ch->inviteOnly)
            {
                if (!key.empty() && key == ch->getKey())
                {
                    send_to_clients(ch, cl, "JOIN :" + ch->getName());
                    ch->addMember(cl, MEMBER);
                    print_infos_after_join(getClientsChannel(ch), cl, ch);
                }
                else if (ch->checkIsInvited(&cl))
                {
                    send_to_clients(ch, cl, "JOIN :" + ch->getName());
                    ch->addMember(cl, MEMBER);
                    print_infos_after_join(getClientsChannel(ch), cl, ch);
                }
                else
                {
                    cl.responsefromServer(ERR_INVITEONLYCHAN(cl.getNickname(), ch->getName()));
                    return ;
                }
            }
            else if (ch->isProtected && !ch->inviteOnly)
            {
                if (key != ch->getKey())
                {
                    cl.responsefromServer(ERR_BADCHANNELKEY(cl.getNickname(), ch->getName()));
                    return ;
                }
                send_to_clients(ch, cl, "JOIN :" + ch->getName());
                ch->addMember(cl, MEMBER);
                print_infos_after_join(getClientsChannel(ch), cl, ch);
            }
            else if (!ch->isProtected && ch->inviteOnly)
            {
                if (!ch->checkIsInvited(&cl))
                {
                    cl.responsefromServer(ERR_INVITEONLYCHAN(cl.getNickname(), ch->getName()));
                    return ;
                }
                send_to_clients(ch, cl, "JOIN :" + ch->getName());
                ch->addMember(cl, MEMBER);
                print_infos_after_join(getClientsChannel(ch), cl, ch);
            }
            else if (!ch->isProtected && !ch->inviteOnly)
            {
                send_to_clients(ch, cl, "JOIN :" + ch->getName());
                ch->addMember(cl, MEMBER);
                print_infos_after_join(getClientsChannel(ch), cl, ch);
            }
        }
        else
        {
            cl.response(ERR_USERONCHANNEL(cl.getNickname(), ch->getName()));
            return ;
        }
    }
    else {
        if (!key.empty())
        {
            _Channels.push_back(Channels(channel, key, cl));
        }
        else
        {
            _Channels.push_back(Channels(channel, cl));
        }
        cl.response("JOIN :" + channel);
        cl.responsefromServer(RPL_NAMREPLY(cl.getNickname(), channel, "@" + cl.getNickname()));
        cl.responsefromServer(RPL_ENDOFNAMES(cl.getNickname(), channel));
    }
}

void server::join(std::vector<std::string> params, std::map<int, client>::iterator c) {
    
    if (params.size() == 1)
    {
        c->second.response(ERR_NEEDMOREPARAMS(c->second.getNickname()));
        return ;
    }
    if (!check_channel_name(params[1]))
    {
        c->second.response(ERR_BADCHANNAME(c->second.getNickname()));
        return ; 
    }
    std::string key = "";
    if (params.size() > 2)
        key = params[2];
    
    join_to_channel(params[1], key, c->second);
}