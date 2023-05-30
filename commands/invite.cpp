/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:28:06 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/30 16:41:59 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

// void server::invite(std::vector<std::string> params, std::map<int, client>::iterator client) {
    
//     if (params.size() < 3)
//     {
//         client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
//         return ;
//     }
    
//     Channels *ch = getChannel(params[2]);
//     if (!ch)
//     {
//         client->second.responsefromServer(ERR_NOSUCHCHANNEL(client->second.getNickname(), params[2]));
//         return ;
//     }

    // if (checkUserIsInChannel(client->second, ch) && checkUserIsInChannel(client->second, ch)->second != OPERATOR)
//     {
//         client->second.responsefromServer(ERR_CHANOPRIVSNEEDED(client->second.getNickname(), ch->getName()));
//         return ;
//     }

//     class::client *c = get_client(params[1]);
//     if (!c)
//     {
//         client->second.responsefromServer(ERR_NOSUCHNICK(client->second.getNickname(), params[1]));
//         return ;
//     }
    
//     if (checkUserIsInChannel(*c, ch))
//     {
//         client->second.responsefromServer(ERR_USERONCHANNEL(client->second.getNickname(), ch->getName()));
//         return ;
//     }

//     ch->addToListInvite(*c);
//     client->second.responsefromServer(RPL_INVITING(client->second.getNickname(), c->getNickname(), ch->getName()));
//     client->second.responsefromServer("NOTICE @"+ch->getName() + " :" + client->second.getNickname() + " invited " + c->getNickname() + " into channel " + ch->getName());
//     sendToClient(c->getsocket(), c->getNickname(), ch->getName(), client->second, "INVITE");
// }



// int   server::findClientByName(std::string nick, client client)
// {
//     std::map<int, client>::iterator it = _connectedClients.begin();
//     for (; it != _connectedClients.end(); it++)
//     {
//         if (nick == it->second.getNickname())
//             return 1;
//     }
//     return -1;
// }

void server::invite(std::vector<std::string> params, std::map<int, client>::iterator cl)
{
    std::string nick = params[1];

    int channelExist = findChannelByName(params[2], cl->second);
    int clientExist = findClientByName(params[1], cl->second);
    if (channelExist == 1)
    {
        Channels *ch = getChannel(params[2]);
        if (clientExist == 1)
        {
            if (ch->isProtected)
            {
                if (isOperator(cl->second, ch))
                {    
                    client *c = get_client(params[1]);
                    if (!checkUserIsInChannel1(*c, ch))
                    {
                        ch->addToListInvite(*c);
                        cl->second.responsefromServer(RPL_INVITING(cl->second.getNickname(), c->getNickname(), ch->getName()));
                        cl->second.responsefromServer("NOTICE @"+ch->getName() + " :" + cl->second.getNickname() + " invited " + c->getNickname() + " into channel " + ch->getName());
                        sendToClient(c->getsocket(), c->getNickname(), ch->getName(), cl->second, "INVITE");  
                    }
                    else
                    {
                        cl->second.responsefromServer(ERR_USERONCHANNEL(cl->second.getNickname(), ch->getName()));
                        return ;   
                    }
                    
                }
                else
                {
                    cl->second.responsefromServer(ERR_CHANOPRIVSNEEDED(cl->second.getNickname(), ch->getName()));
                }
            }
            else if (ch->inviteOnly)
            {
                if (isOperator(cl->second, ch))
                {    
                    client *c = get_client(params[1]);
                    if (!checkUserIsInChannel1(*c, ch))
                    {
                        ch->addToListInvite(*c);
                        cl->second.responsefromServer(RPL_INVITING(cl->second.getNickname(), c->getNickname(), ch->getName()));
                        cl->second.responsefromServer("NOTICE @"+ch->getName() + " :" + cl->second.getNickname() + " invited " + c->getNickname() + " into channel " + ch->getName());
                        sendToClient(c->getsocket(), c->getNickname(), ch->getName(), cl->second, "INVITE");  
                    }
                    else
                    {
                        cl->second.responsefromServer(ERR_USERONCHANNEL(cl->second.getNickname(), ch->getName()));
                        return ;   
                    }
                    
                }
                else
                {
                    cl->second.responsefromServer(ERR_CHANOPRIVSNEEDED(cl->second.getNickname(), ch->getName()));
                }
            }
            else
            {
                client *c = get_client(params[1]);
                if (checkUserIsInChannel1(*c, ch))
                {
                    ch->addToListInvite(*c);
                    cl->second.responsefromServer(RPL_INVITING(cl->second.getNickname(), c->getNickname(), ch->getName()));
                    cl->second.responsefromServer("NOTICE @"+ch->getName() + " :" + cl->second.getNickname() + " invited " + c->getNickname() + " into channel " + ch->getName());
                    sendToClient(c->getsocket(), c->getNickname(), ch->getName(), cl->second, "INVITE"); 
                }
                else
                {
                    cl->second.responsefromServer(ERR_USERONCHANNEL(cl->second.getNickname(), ch->getName()));
                }

            }   
        }
    }
}
