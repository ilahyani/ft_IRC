/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:08:28 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/07 00:50:13 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

bool check_channel_name(std::string channel)
{
    std::string invalidChars = " ,:;-?!&%\\/()[]{}\"'~^$#*";

    if (channel[0] != '#')
        return false;
    
    for (int i = 1; i < (int)channel.length(); i++)
    {
        if (invalidChars.find(channel[i]) != std::string::npos)
            return false;
    }
    return true;
}

void server::join_to_channel(std::string channel, std::string key, client &client)
{
    Channels *ch = getChannel(channel);
    if (ch != NULL && ch->getName() == channel){
        if (client.getNickname() != ch->getOwnerNickname())
        {
            if (ch->isProtected)
            {
                if (key != ch->getKey())
                {
                    client.response(ERR_BADCHANNELKEY(client.getNickname()));
                    return ;
                }
                ch->addMember(client, true);
            }
            else if (!ch->isProtected)
            {
                ch->addMember(client, true);
            }
        }
        else
            client.response(ERR_USERONCHANNEL(client.getNickname(), ch->getName()));
    }
    else {
        if (!key.empty())
            _Channels.push_back(Channels(channel, key, client));
        else
            _Channels.push_back(Channels(channel, client));
    }
}

void server::join(std::vector<std::string> params, std::map<int, client>::iterator client) {
    
    if (params.size() < 2)
    {
        client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }
    
    if (!check_channel_name(params[1]))
    {
        client->second.response(ERR_BADCHANNAME(client->second.getNickname()));
        return ; 
    }

    std::string key = "";

    if (params.size() > 2)
        key = params[2];
    
    join_to_channel(params[1], key, client->second);

    std::vector<Channels>::iterator it = _Channels.begin();
    while (it != _Channels.end())
    {
        std::cout << "channel : " << it->getName() << std::endl;
        it++;
    }
    
    std::cout << "JOIN command called\n";
}