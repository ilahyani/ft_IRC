/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:28:06 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/01 23:38:45 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::invite(std::vector<std::string> params, std::map<int, client>::iterator client) {
    
    if (params.size() < 3)
    {
        client->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }
    
    Channels *ch = getChannel(params[2]);
    if (!ch)
    {
        client->second.ServertoClientPrefix(ERR_NOSUCHCHANNEL(client->second.getNickname(), params[2]));
        return ;
    }

    if (checkUserIsInChannel(client->second, ch) && checkUserIsInChannel(client->second, ch)->second != OPERATOR)
    {
        client->second.ServertoClientPrefix(ERR_CHANOPRIVSNEEDED(client->second.getNickname(), ch->getName()));
        return ;
    }

    class::client *c = get_client(params[1]);
    if (!c)
    {
        client->second.ServertoClientPrefix(ERR_NOSUCHNICK(client->second.getNickname(), params[1]));
        return ;
    }
    
    if (checkUserIsInChannel(*c, ch))
    {
        client->second.ServertoClientPrefix(ERR_USERONCHANNEL(client->second.getNickname(), ch->getName()));
        return ;
    }

    ch->addToListInvite(*c);
    client->second.ServertoClientPrefix(RPL_INVITING(client->second.getNickname(), c->getNickname(), ch->getName()));
    client->second.ServertoClientPrefix("NOTICE @"+ch->getName() + " :" + client->second.getNickname() + " invited " + c->getNickname() + " into channel " + ch->getName());
    sendToClientById(c->getsocket(), client->second, "INVITE " + c->getNickname() + " :" + ch->getName());
}