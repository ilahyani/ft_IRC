/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:53:41 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/01 16:30:34 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

// bool isMember(const client& client) {
//     for (size_t i = 0; i < _Members.size(); i++) {
//         if (_Members[i].first == client && _Members[i].second == MEMBER) {
//             return true;
//         }
//     }
//     return false;
// }

void server::send_message_to_channel1(std::string channel, std::string receiver , std::string message, client c)
{
    Channels *ch = getChannel(channel);
    if (ch == NULL || channel != ch->getName())
    {
        c.response(ERR_NOSUCHCHANNEL(c.getNickname(), channel));
        return ;
    }
    std::vector<std::pair<client, ROLE> > members = ch->getMembers();
    for (int i = 0; i < (int)members.size(); i++)
    {
        if (members[i].first.getsocket() == c.getsocket())
            i++;
        if ((int)members.size() == i)
            break;
        sendToClient2(members[i].first.getsocket(), channel, receiver, message, c, "KICK");
    }
}


void server::kick(std::vector<std::string> params, std::map<int, client>::iterator c)
{
    std::cout << "KCIK command called\n";

    int channelExist = findChannelByName(params[1], c->second);
    int clientExist = findClientByName(params[2], c->second);

    if (params.size() >= 3)
    {
        std::cout << "number of params "<< params.size() << std::endl;
        if (channelExist == 1)
        {
            Channels *ch = getChannel(params[1]);
            if (clientExist == 1)
            {
                client *receiver = findClientByName1(params[2]);
                if (checkUserIsInChannel1(*receiver, ch))
                {
                    
                    if (isOperator(c->second, ch))
                    {    
                        if (c->second.getsocket() != receiver->getsocket())
                        {
                            std::vector<std::pair<client, ROLE> >::iterator channelMember = ch->getMembers().end();
                            for (std::vector<std::pair<client, ROLE> >::iterator it = ch->getMembers().begin(); it != ch->getMembers().end(); ++it)
                            {
                                if (it->first.getsocket() == receiver->getsocket())
                                {
                                    channelMember = it;
                                    break;
                                }
                            }
                            if (params.size() == 3)
                                send_message_to_channel1(params[1], params[2] ,"no reason",  c->second);
                            else
                                send_message_to_channel1(params[1], params[2] ,params[3],  c->second);
                            ch->getMembers().erase(channelMember);
                        }
                        else
                            return ;
                    }
                    else
                        c->second.responsefromServer(ERR_CHANOPRIVSNEEDED(c->second.getNickname(), ch->getName()));
                }
                
            }
        }
    }
    else
    {
        if (params.size() < 2)
            c->second.responsefromServer(ERR_NEEDMOREPARAMS(c->second.getNickname()));   
    }
}