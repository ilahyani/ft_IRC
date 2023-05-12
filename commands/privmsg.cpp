/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:18:50 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/13 00:18:20 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void    server::sendToClient(std::string receiver, std::string nick_or_channel, std::string message, client sender)
{
    std::string msg = ":" + sender.get_format() + " PRIVMSG " + nick_or_channel + " :" + message + "\n";
    if(get_client(receiver))
    {
        if (send(get_client(receiver)->getsocket(), msg.c_str(), msg.length(), 0) < 0)
            throw std::runtime_error("An error occurred while attempting to send a message to the client.\n");
    }
    msg.clear();
}

void server::send_message_to_user(std::string nick, std::string message, client client)
{
    if (get_client(nick) == NULL || nick != get_client(nick)->getNickname())
    {
        client.response(ERR_NOSUCHNICK(client.getNickname()));
        return ;
    }
    sendToClient(nick, nick, message, client);
}

void server::send_message_to_channel(std::string channel, std::string message, client c)
{
    Channels *ch = getChannel(channel);
    if (ch == NULL || channel != ch->getName())
    {
        c.response(ERR_NOSUCHCHANNEL(channel));
        return ;
    }

    std::vector<client> members = ch->getMembers();
    for (int i = 0; i < (int)members.size(); i++)
    {
        if (members[i].getNickname() == c.getNickname())
            i++;
        if ((int)members.size() == i)
            break;
        sendToClient(members[i].getNickname(), channel, message, c);
    }
    if (c.getNickname() != ch->getOwnerNickname())
        sendToClient(ch->getOwnerNickname(), channel, message, c);
}

void server::privmsg(std::vector<std::string> params, std::map<int, client>::iterator client) {

    std::string message;

    if (params.size() < 3)
    {
        client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }
    if (params[2][0] != ':')
        return ;
    message = params[2].substr(1, params[2].size()) + " ";
    for (int i = 3; i < (int)params.size(); i++)
        message += params[i] + " ";
    
    if (params[1][0] == '#')
        send_message_to_channel(params[1], message, client->second);
    else
        send_message_to_user(params[1], message, client->second);
}