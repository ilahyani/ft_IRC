/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallops.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 00:45:04 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/31 00:00:13 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::wallops(std::vector<std::string> params, std::map<int, client>::iterator cl) {
    
    if (params.size() < 2)
    {
        cl->second.responsefromServer(ERR_NEEDMOREPARAMS(cl->second.getNickname()));
        return ;
    }

    if (!cl->second.isOpreator)
    {
        cl->second.responsefromServer(ERR_NOPRIVILEGES(cl->second.getNickname()));
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