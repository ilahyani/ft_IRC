/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:07:57 by oqatim            #+#    #+#             */
/*   Updated: 2023/05/31 19:34:09 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::quit(std::vector<std::string> params, std::map<int, client>::iterator c)
{
    std::cout << "QUIT command called\n";

    if (params.size() == 2)
    {
        int clientExist = findClientByName(c->second.getNickname(), c->second);
        int fd_client = c->second.getsocket();
        std::map<int, client>::iterator	itClient = _connectedClients.find(fd_client);
        if (clientExist == 1)
        {
            for(size_t i = 0; i < _Channels.size(); i++)
            {
                Channels *ch = getChannel(_Channels[i].getName());
                if (checkUserIsInChannel1(c->second, ch))
                {
                    std::vector<std::pair<client, ROLE> >::iterator channelMember = ch->getMembers().end();
                    for (std::vector<std::pair<client, ROLE> >::iterator it = ch->getMembers().begin(); it != ch->getMembers().end(); ++it)
                    {
                        if (it->first.getsocket() == c->second.getsocket())
                        {
                            channelMember = it;
                            break;
                        }
                    }
                    ch->getMembers().erase(channelMember);
                }
            }
            if (itClient != _connectedClients.end())
            {
               _connectedClients.erase(itClient); 
            }
            
            std::cout << "CLIENT DISCONNECTED \n";
            close(fd_client);
        }
    }
    else
    {
        if (params.size() < 2)
            c->second.responsefromServer(ERR_NEEDMOREPARAMS(c->second.getNickname()));
        else
            return ;
    }
}