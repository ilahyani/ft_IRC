/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:18:50 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/16 19:24:44 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::send_message_to_user(std::string nick, std::string message, client client)
{
    if (get_client(nick) == NULL || nick != get_client(nick)->getNickname())
    {
        client.response(ERR_NOSUCHNICK(client.getNickname()));
        return ;
    }
    sendToClient(nick, nick, message, client, "PRIVMSG");
}

void server::send_message_to_channel(std::string channel, std::string message, client c)
{
    Channels *ch = getChannel(channel);
    if (ch == NULL || channel != ch->getName())
    {
        c.response(ERR_NOSUCHCHANNEL(c.getNickname(), channel));
        return ;
    }

    std::vector<client> members = ch->getMembers();
    for (int i = 0; i < (int)members.size(); i++)
    {
        if (members[i].getNickname() == c.getNickname())
            i++;
        if ((int)members.size() == i)
            break;
        sendToClient(members[i].getNickname(), channel, message, c, "PRIVMSG");
    }
    if (c.getNickname() != ch->getOwnerNickname())
        sendToClient(ch->getOwnerNickname(), channel, message, c, "PRIVMSG");
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