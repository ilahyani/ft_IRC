/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:53:41 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/01 23:38:45 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::kick(std::vector<std::string> params, std::map<int, client>::iterator client) {

    if (params.size() < 3)
    {
        client->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }

    Channels* ch = getChannel(params[1]);
    if (!ch)
    {
        client->second.ServertoClientPrefix(ERR_NOSUCHCHANNEL(client->second.getNickname(), params[1]));
        return ;
    }

    if (!checkUserIsInChannel(client->second, ch))
    {
        client->second.ServertoClientPrefix(ERR_NOTONCHANNEL(client->second.getNickname(), params[1]));
        return ;
    }

    if (checkUserIsInChannel(client->second, ch)->second != OPERATOR)
    {
        client->second.ServertoClientPrefix(ERR_CHANOPRIVSNEEDED(client->second.getNickname(), params[1]));
        return ;
    }

    class::client* cl = get_client(params[2]);
    if (!get_client(params[2]))
        return ;

    if (!checkUserIsInChannel(*cl, ch))
    {
        client->second.ServertoClientPrefix(ERR_USERNOTINCHANNEL(client->second.getNickname(), cl->getNickname(), ch->getName()));
        return ;
    }

    std::string reason;
    if (params.size() == 4)
        reason = params[3];
    else 
        reason = ":" + client->second.getNickname();
    send_to_all_in_channel(ch, client->second, "KICK " + ch->getName() + " " + cl->getNickname() + " " + reason);
    ch->removeMember(*cl);
}