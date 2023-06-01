/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:07:30 by oqatim            #+#    #+#             */
/*   Updated: 2023/05/31 17:09:50 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"


void sendMessage(int fd, std::string message)
{
	size_t i = 0;
	message += "\r\n";
	while (i != message.length())
		i += send(fd, message.c_str(), message.length() - i, 0);
}

void cmd_Resp_Handler1(int sender_fd, int cmd_resp_code, std::string serverName, std::string nickName, std::string channelName, std::string arg2, std::string arg3) /**/
{
	std::string message;
	switch (cmd_resp_code)
	{
        case 322 :
            message = ":" + serverName + " 322 " + nickName + " " + channelName + " " + arg2 + " " + arg3;
            break;
        case 341 :
            message = ":" + serverName + " 341 " + nickName + " " + arg2 + "  " + channelName;
            break;
        case 353 :
            message = ":" + serverName + " 353 " + nickName + " = " + channelName + " :" + arg2;
            break;
        case 352 :
            message = ":" + serverName + " 353 " + nickName + " = " + channelName + " : " + arg2;
            break;
        case 366 :
            message = ":" + serverName + " 366 " + nickName + " " + channelName +" :End of /NAMES list";
            break;
		default:
			std::cout << "Invalid command response code 2" << std::endl;
	}
	sendMessage(sender_fd, message);
}

void server::names(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "NAMES command called\n";

    int k = 0;
    if (params.size() == 1)
    {
        if (_Channels.size() != 0)
        {
            if (k == 1)
            {
                return;
            }
            else
            {
                for (size_t i = 0; i < _Channels.size(); i++)
                {
                    std::string channelUsers = "";
                    std::string Channel_name;
                    std::string str;
                    for (size_t j = 0; j < _Channels[i].getMembers().size(); j++)
                    {
                        std::string client_Nick = _Channels[i].getMembers().at(j).first.getNickname();
                        Channel_name = _Channels[i].getName();
                        channelUsers = channelUsers.append(" ") + client_Nick;
                    }
                    str = "Channel " + Channel_name + " : " + channelUsers;
                    // client->second.response(str);
                    cmd_Resp_Handler1(client->second.getsocket(), 353, "bobiza", client->second.getNickname(), _Channels[i].getName(), channelUsers , std::string(""));
                }
                cmd_Resp_Handler1(client->second.getsocket(), 366, "bobiza", client->second.getNickname(), std::string("*") , std::string("") , std::string(""));
            }
        }
    }
    if (params.size() == 2)
    {
        if (check_multichannel(params[1]))
        {
            std::vector<std::string> Channels_list = ft_split_channels(params[1]);
            for (size_t i = 0; i < Channels_list.size(); i++)
            {
                int channelExist = findChannelByName(Channels_list[i], client->second);
                if (channelExist == 1)
                {
                    Channels *ch = getChannel(Channels_list[i]);
                    if (k == 1)
                    {
                        return ;
                    }
                    else
                    {
                        for (size_t j = 0; j < ch->getMembers().size(); j++)
                        {
                            std::string client_Nick = ch->getMembers().at(j).first.getNickname();
                            std::string Channel_name = ch->getName();
                            std::string str = "Channel " + Channel_name + " : " + client_Nick;
                            client->second.response(str);
                        }
                    }
                }
            }
        }
        else
        {
            int channelExist = findChannelByName(params[1], client->second);
            if (channelExist == 1)
            {
                Channels *ch = getChannel(params[1]);
                if (k == 1)
                {
                    return ;
                }
                else
                {
                    for (size_t j = 0; j < ch->getMembers().size(); j++)
                    {
                        std::string client_Nick = ch->getMembers().at(j).first.getNickname();
                        std::string Channel_name = ch->getName();
                        std::string str = "Channel " + Channel_name + " : " + client_Nick;
                        client->second.response(str);
                    }
                }
            }
        }
    }
    else 
    {
        return ;
    }
    client->second.response(": End of /NAMES list");
}