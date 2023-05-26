/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:07:41 by oqatim            #+#    #+#             */
/*   Updated: 2023/05/26 11:07:47 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::send_message_to_user_n(std::string nick, std::string message, client c)
{
    client *cl = get_client(nick);
    if (!cl)
    {
        c.response(ERR_NOSUCHNICK(c.getNickname(), nick));
        return ;
    }
    sendToClient(cl->getsocket(), nick, message, c, "PRIVMSG");
}

void server::send_message_to_channel_n(std::string channel, std::string message, client c)
{
    Channels *ch = getChannel(channel);
    if (ch == NULL || channel != ch->getName())
    {
        c.response(ERR_NOSUCHCHANNEL(c.getNickname(), channel));
        return ;
    }
    std::vector<std::pair<client, ROLE> > members = ch->getMembers();
    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i].first.getsocket() == c.getsocket())
            i++;
        if (members.size() == i)
            break;
        sendToClient(members[i].first.getsocket(), channel, message, c, "PRIVMSG");
    }
}

void server::notice(std::vector<std::string> params, std::map<int, client>::iterator client) {
    
    if (params.size() < 3)
    {
        if(params[1].empty())
        {
            client->second.response(ERR_NORECIPIENT(client->second.getNickname(), params[0]));
            return ;
        }
        else if (params[2].empty())
        {
            client->second.response(ERR_NOTEXTTOSEND(client->second.getNickname()));
            return ;
        }
    }
    
    if (params[1][0] == '#')
        send_message_to_channel(params[1], params[2], client->second);
    else
        send_message_to_user(params[1], params[2], client->second);
}
