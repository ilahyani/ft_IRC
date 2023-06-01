/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:26:07 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/01 18:27:28 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

// void server::send_message_to_channel_n(std::string channel, std::string message, client c)
// {
//     Channels *ch = getChannel(channel);
//     if (ch == NULL || channel != ch->getName())
//     {
//         c.response(ERR_NOSUCHCHANNEL(c.getNickname(), channel));
//         return ;
//     }
//     std::vector<std::pair<client, ROLE> > members = ch->getMembers();
//     for (size_t i = 0; i < members.size(); i++)
//     {
//         if (members[i].first.getsocket() == c.getsocket())
//             i++;
//         if (members.size() == i)
//             break;
//         sendToClient(members[i].first.getsocket(), channel, message, c, "");
//     }
// }

void    server::sendToClient3(int receiver, std::string nick_or_channel, client sender, std::string cmd)
{
    std::string msg = ":" + sender.get_format() + cmd + " :" + nick_or_channel + "\n";
    if(Check_client(receiver))
    {
        if (send(receiver, msg.c_str(), msg.length(), 0) < 0)
            throw std::runtime_error("An error occurred while attempting to send a message to the client.\n");
    }
    msg.clear();
}

void server::send_message_to_channel2(std::string channel, client c)
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
        // if (members[i].first.getsocket() == c.getsocket())
        //     i++;
        // if ((int)members.size() == i)
        //     break;
        sendToClient3(members[i].first.getsocket(), channel, c, "PART");
    }
}

void server::part(std::vector<std::string> params, std::map<int, client>::iterator c) {
    std::cout << "PART command called\n";
    
    if (params.size() >= 2)
    {
        if (check_multichannel(params[1]))
        {
            std::vector<std::string> Channels_list = ft_split_channels(params[1]);
            for (size_t i = 0; i < Channels_list.size(); i++)
            {
                int channelExist = findChannelByName(Channels_list[i], c->second);
                if (channelExist == 1)
                {
                    Channels *ch = getChannel(Channels_list[i]);
                    if (checkUserIsInChannel1(c->second, ch))
                    {
                        std::vector<std::pair<client, ROLE> >::iterator channelMember = ch->getMembers().end();
                        for (std::vector<std::pair<client, ROLE> >::iterator it = ch->getMembers().begin(); it != ch->getMembers().end(); ++it) {
                            if (it->first.getsocket() == c->second.getsocket())
                            {
                                channelMember = it;
                                break;
                            }
                        }
                        send_message_to_channel2(ch->getName(),  c->second);
                        ch->getMembers().erase(channelMember);
                        
                    }
                    else
                    {
                        c->second.response(ERR_NOTONCHANNEL(c->second.getNickname(), params[1]));
                    }
                }
            }
        }
        else
        {
            int channelExist = findChannelByName(params[1], c->second);
            if (channelExist == 1)
            {
                Channels *ch = getChannel(params[1]);
                if (checkUserIsInChannel1(c->second, ch))
                {
                    std::vector<std::pair<client, ROLE> >::iterator channelMember = ch->getMembers().end();
                    for (std::vector<std::pair<client, ROLE> >::iterator it = ch->getMembers().begin(); it != ch->getMembers().end(); ++it) {
                        if (it->first.getsocket() == c->second.getsocket())
                        {
                            channelMember = it;
                            break;
                        }
                    }
                    send_message_to_channel2(params[1],  c->second);
                    ch->getMembers().erase(channelMember);
                }
                else
                {
                    c->second.response(ERR_NOTONCHANNEL(c->second.getNickname(), params[1]));
                }
            }
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