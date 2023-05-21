/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:07:19 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/20 22:54:26 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void    server::send_msg_to_all_users(Channels *ch, std::string msg, client c)
{
    std::vector<std::pair<client, ROLE> > clients = ch->getMembers();

    int i = 0;
    while (i < (int)clients.size())
    {
        sendToClient(clients[i].first.getNickname(), ch->getName() , msg, c, "TOPIC");
        i++;
    }
    sendToClient(c.getNickname(), ch->getName() , msg, c, "TOPIC");
}

void server::topic(std::vector<std::string> params, std::map<int, client>::iterator c) {

    if (params.size() < 2)
    {
        c->second.response(ERR_NEEDMOREPARAMS(c->second.getNickname()));
        return ;
    }
    
    Channels *ch = getChannel(params[1]);
    if (!ch)
    {
        c->second.responsefromServer(ERR_NOSUCHCHANNEL(c->second.getNickname(), params[1]));
        return ;
    }
    
    if (!checkUserIsInChannel(c->second, ch))
    {
        c->second.responsefromServer(ERR_NOTONCHANNEL(c->second.getNickname(), params[1]));
        return ;
    }

    if (params.size() == 2 && ch && ch->geTopic().empty())
    {
        c->second.responsefromServer(RPL_NOTOPIC(c->second.getNickname(), params[1]));
        return ;
    }

    if (params.size() == 2 && ch && !ch->geTopic().empty())
    {
        c->second.responsefromServer(RPL_TOPIC(c->second.getNickname(), params[1], ch->geTopic()));
        return ;
    }

    ch->setTopic(params[2]);
    send_msg_to_all_users(ch, params[2], c->second);
}