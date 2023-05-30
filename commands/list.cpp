/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:07:22 by oqatim            #+#    #+#             */
/*   Updated: 2023/05/30 22:02:02 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"


void sendMessage1(int fd, std::string message)
{
	size_t i = 0;
	message += "\r\n";
	while (i != message.length())
		i += send(fd, message.c_str(), message.length() - i, 0);
}

void cmd_Resp_Handler2(int sender_fd, int cmd_resp_code, std::string serverName, std::string nickName, std::string channelName, std::string arg2, std::string arg3) /**/
{
    (void) cmd_resp_code;
	std::string message = ":" + serverName + " 322 " + nickName + " " + channelName + " " + arg2 + " " + arg3;
   
	sendMessage1(sender_fd, message);
}

void cmd_Resp_Handler3(int sender_fd, int cmd_resp_code, std::string serverName, std::string nickName) /**/
{
    (void) cmd_resp_code;
	std::string     message = ":" + serverName + " 323 " + nickName + " :End of /LIST";

	sendMessage1(sender_fd, message);
}

bool check_multichannel(const std::string& str)
{
    return str.find(',') != std::string::npos;
}


std::vector<std::string> ft_split_channels(std::string channels)
{
    std::vector<std::string> channelList;

    std::istringstream iss(channels);
    std::string channel;
    
    while (std::getline(iss, channel, ','))
    {
        channelList.push_back(channel);
    }
    return (channelList);
}

void server::list(std::vector<std::string> params, std::map<int, client>::iterator client)
{
    std::cout << "LIST command called\n";

    client->second.responsefromServer("Channel :Users Name");
    
    int k = 0;
    if (params.size() == 1)
    {
        if (_Channels.size() != 0)
        {
            for (int i = 0; i < (int)_Channels.size(); i++)
            {
                if (k == 1)
                {
                    std::string Channel_name = _Channels[i].getName();
                    std::string str = "Channel " + Channel_name + " : Private";
                    client->second.responsefromServer(str);
                }
                else
                {
                    std::string Channel_name = _Channels[i].getName();
                    std::string str = "Channel " + Channel_name + " : " + _Channels[i].geTopic();
                    // client->second.responsefromServer(str);// "prv"
                    
                    cmd_Resp_Handler2(client->second.getsocket(), 322, "khobza" , client->second.getNickname() , Channel_name, std::to_string(10), "prv");
                }

            }
        }
    }
    else if (params.size() == 2)
    {

            if (check_multichannel(params[1]))
            {
                std::vector<std::string> Channels_list = ft_split_channels(params[1]);
                for (size_t i = 0; i < Channels_list.size(); i++)
                {
                    int channelExist = findChannelByName(Channels_list[i], client->second);
                    if (channelExist == 1)
                    {
                        if (k == 1)
                        {
                            std::string Channel_name = _Channels[i].getName();
                            std::string str = "Channel " + Channel_name + " : Private";
                            // client->second.responsefromServer(str);
                            cmd_Resp_Handler2(client->second.getsocket(), 322, "khobza" , client->second.getNickname() , Channel_name, std::to_string(10), _Channels[i].geTopic());
                        }
                        else
                        {
                            std::string Channel_name = _Channels[i].getName();
                            std::string str = "Channel " + Channel_name + " : " + _Channels[i].geTopic();
                            // client->second.responsefromServer(str);
                            cmd_Resp_Handler2(client->second.getsocket(), 322, "khobza" , client->second.getNickname() , Channel_name, std::to_string(10), _Channels[i].geTopic());
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
                        std::string Channel_name = ch->getName();
                        std::string str = "Channel " + Channel_name + " : Private";
                        client->second.responsefromServer(str);
                    }
                    else
                    {
                        std::string Channel_name = ch->getName();
                        std::string str = "Channel " + Channel_name + " : " + ch->geTopic();
                        client->second.responsefromServer(str);
                    }

                }
            }
        
    }
    else
    {
        return ;
    }
    // cmd_Resp_Handler3(client->second.getsocket(), 323, "khobza", client->second.getNickname());
    // client->second.responsefromServer(":End of /LIST");
       
}