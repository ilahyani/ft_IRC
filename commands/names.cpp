/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:31:12 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/01 23:38:45 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::names(std::vector<std::string> params, std::map<int, client>::iterator client) {
    
    if (params.size() < 2)
    {
        client->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }
    Channels *ch = getChannel(params[1]);
    if (!ch)
        return ;
    if (ch && checkUserIsInChannel(client->first, ch))
    {
        client->second.ServertoClientPrefix(RPL_NAMREPLY(client->second.getNickname(), ch->getName(), getClientsChannel(ch)));
        client->second.ServertoClientPrefix(RPL_ENDOFNAMES(client->second.getNickname(), ch->getName()));
        return ;
    }
    client->second.ServertoClientPrefix(RPL_NAMREPLY(client->second.getNickname(), ch->getName(), ""));
    client->second.ServertoClientPrefix(RPL_ENDOFNAMES(client->second.getNickname(), ch->getName()));
    return ;
}