/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:18:50 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/01 23:38:45 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::send_message_to_user(std::string nick, std::string message, client c)
{
    client *cl = get_client(nick);
    if (!cl)
    {
        c.ServertoClientPrefix(ERR_NOSUCHNICK(c.getNickname(), nick));
        return ;
    }
    sendToClientById(cl->getsocket(), c, "PRIVMSG " + cl->getNickname() + " :" + message);
}

void server::send_message_to_channel(std::string channel, std::string message, client c)
{
    Channels *ch = getChannel(channel);
    if (!ch || channel != ch->getName())
    {
        c.ServertoClientPrefix(ERR_NOSUCHCHANNEL(c.getNickname(), channel));
        return ;
    }
    send_msg_to_clients_who_in_channel(ch, c, "PRIVMSG " + ch->getName() + " :" + message);
}

void server::privmsg(std::vector<std::string> params, std::map<int, client>::iterator client) {

    if (params.size() < 2)
    {
        client->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }

    if (params.size() < 3)
    {
        client->second.ServertoClientPrefix(ERR_NOTEXTTOSEND(client->second.getNickname()));
        return ;
    }

    if (params[1][0] == '#' && params[1].size() > 1)
        send_message_to_channel(params[1], params[2], client->second);
    else
        send_message_to_user(params[1], params[2], client->second);
}