/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:08:28 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/16 19:50:45 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"
#include "../client.hpp"

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

void    send_to_clients(Channels *ch, client c)
{
    int i = 0;
    std::vector<client> clients = ch->getMembers();
    std::string message = ":" + c.get_format() + " JOIN :" + ch->getName() + "\n";
    client owner = ch->getOwner();
    while (i < (int)clients.size())
    {
        send(clients[i].getsocket(), message.c_str(), message.length(), 0);
        i++;
    }
    send(owner.getsocket(), message.c_str(), message.length(), 0);
}

std::string getClientsChannel(Channels *ch)
{
    std::string str;
    std::vector<client> clients = ch->getMembers();


    int i = clients.size() - 1;
    while (i >= 0)
    {
        str += (clients[i].getNickname() + " ");
        i--;
    }
    str += ("@" + ch->getOwnerNickname());
    
    return str;
}

void    print_infos_after_join(std::string clients_of_channel, client &client, std::string channel)
{
    client.response("JOIN :" + channel);
    client.responsefromServer(RPL_NAMREPLY(client.getNickname(), channel, clients_of_channel));
    client.responsefromServer(RPL_ENDOFNAMES(client.getNickname(), channel));
    
    // client.print(":" + client.getHostname() + " " + );
    // client.print(":" + client.getHostname() + " " + RPL_ENDOFNAMES(client.getNickname(), channel));
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
                send_to_clients(ch, client);
                ch->addMember(client, true);
                print_infos_after_join(getClientsChannel(ch), client, channel);
            }
            else if (!ch->isProtected && key.empty())
            {
                send_to_clients(ch, client);
                ch->addMember(client, true);
                print_infos_after_join(getClientsChannel(ch), client, channel);
            }
        }
        else
        {
            client.response(ERR_USERONCHANNEL(client.getNickname(), ch->getName()));
            return ;
        }
    }
    else {
        if (!key.empty())
            _Channels.push_back(Channels(channel, key, client));
        else
            _Channels.push_back(Channels(channel, client));
            print_infos_after_join("@" + client.getNickname(), client, channel);
    }
}

void server::join(std::vector<std::string> params, std::map<int, client>::iterator c) {
    
    if (params.size() < 2)
    {
        c->second.response(ERR_NEEDMOREPARAMS(c->second.getNickname()));
        return ;
    }
    
    if (!check_channel_name(params[1]))
    {
        c->second.response(ERR_BADCHANNAME(c->second.getNickname()));
        return ; 
    }

    std::string key = "";
    if (params.size() > 2)
        key = params[2];
    
    join_to_channel(params[1], key, c->second);
}