/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallops.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 00:45:04 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/01 23:38:45 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::wallops(std::vector<std::string> params, std::map<int, client>::iterator cl) {
    
    if (params.size() < 2)
    {
        cl->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(cl->second.getNickname()));
        return ;
    }

    if (!cl->second.isOpreator)
    {
        cl->second.ServertoClientPrefix(ERR_NOPRIVILEGES(cl->second.getNickname()));
        return ;
    }

    std::map<int, client>::iterator it = _connectedClients.begin();
    while (it != _connectedClients.end())
    {
        if (it->second.wallops && it->second.getsocket() != cl->second.getsocket())
            sendToClientById(it->second.getsocket(), cl->second, "NOTICE " + it->second.getNickname() + " :" + params[1]);
        it++;
    }
}