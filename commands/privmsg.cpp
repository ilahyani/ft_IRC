/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:18:50 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/22 23:29:05 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"
#include "../client.hpp"

void server::send_message_to_user(std::string nick, std::string message, client c)
{
    client *cl = get_client(nick);
    if (!cl)
    {
        c.response(ERR_NOSUCHNICK(c.getNickname(), nick));
        return ;
    }
    sendToClient(cl->getsocket(), nick, message, c, "PRIVMSG");
}

void server::send_message_to_channel(std::string channel, std::string message, client c)
{
    Channels *ch = getChannel(channel);
    if (ch == NULL || channel != ch->getName())
    {
        c.response(ERR_NOSUCHCHANNEL(c.getNickname(), channel));
        return ;
    }
    std::vector<std::pair<client, ROLE> > members = ch->getMembers();
    for (int i = 0; i < (int)members.size(); i++)
    {
        if (members[i].first.getsocket() == c.getsocket())
            i++;
        if ((int)members.size() == i)
            break;
        sendToClient(members[i].first.getsocket(), channel, message, c, "PRIVMSG");
    }
}

void server::privmsg(std::vector<std::string> params, std::map<int, client>::iterator client) {
    
    if (params.size() < 3)
    {
        client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }
    
    if (params[1][0] == '#')
        send_message_to_channel(params[1], params[2], client->second);
    else
        send_message_to_user(params[1], params[2], client->second);
}