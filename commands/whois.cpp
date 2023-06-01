/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:08:08 by oqatim            #+#    #+#             */
/*   Updated: 2023/06/01 19:15:35 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"
#include "../client.hpp"


void sendMessage_w(int fd, std::string message)
{
	size_t i = 0;
	// message += "\r\n";
	while (i != message.length())
		i += send(fd, message.c_str(), message.length() - i, 0);
}

void cmd_Resp_Handler_w(int sender_fd, int cmd_resp_code, std::string serverName, std::string nickName, std::string channelName, std::string arg2, std::string arg3) /**/
{
    (void) cmd_resp_code;
    std::string message;
	message = ":" + serverName + " 322 " + nickName + " " + channelName + " " + arg2 + " " + arg3;  
   
	sendMessage_w(sender_fd, message);
}

void server::whois(std::vector<std::string> params, std::map<int, client>::iterator c)
{
    std::cout << "WHOIS command called\n";

    if(params.size() >= 2)
    {
        if (check_multichannel(params[1]))
        {
            std::vector<std::string> Nick_list = ft_split_channels(params[1]);
            for (size_t i = 0; i < Nick_list.size(); i++)
            {
                int clientExist = findClientByName(Nick_list[i], c->second);
                if (clientExist == 1)
                {
                    // std::string str = client->getNickname() + " " + client->getUsername() + " " + client->getHostname() + " * : " + client->getRealname();
                    // c->second.response(str);
                    client *client = findClientByName1(Nick_list[i]);
                    std::string rpl = ":irc 311 " + client->getNickname() + " " + client->getUsername() + " ~" + client->getUsername() + " " + client->getHostname() + " * :" + client->getRealname() + "\r\n"
							+ ":irc" + " 318 " + client->getNickname() + " " + client->getUsername() + " :End of /WHOIS list.\r\n";
                    sendMessage_w(client->getsocket(), rpl);
                    // cmd_Resp_Handler2(client->second.getsocket(), 322, "khobza" , client->second.getNickname() , Channel_name, std::to_string(10), "prv");
                    // cmd_Resp_Handler2(client->second.getsocket(), 322, "khobza" , client->second.getNickname() , Channel_name, std::to_string(10), "prv");

                }
            }
        }
        else
        {
            int clientExist = findClientByName(params[1], c->second);
            if (clientExist == 1)
            {
                    client *client = findClientByName1(params[1]);
                    std::string rpl = ":irc 311 " + client->getNickname() + " " + client->getUsername() + " ~" + client->getUsername() + " " + client->getHostname() + " * :" + client->getRealname() + "\r\n"
							+ ":irc" + " 318 " + client->getNickname() + " " + client->getUsername() + " :End of /WHOIS list.\r\n";
                    sendMessage_w(c->second.getsocket(), rpl);
                    // std::string rpl = ":irc 311 " + c->second.getNickname() + " " + c->second.getUsername() + " ~" + c->second.getUsername() + " " + c->second.getHostname() + " * :" + c->second.getRealname() + "\r\n"
					// 		+ ":irc" + " 318 " + c->second.getNickname() + " " + c->second.getUsername() + " :End of /WHOIS list.\r\n";
                    // sendMessage_w(c->second.getsocket(), rpl);
                    
                // std::string str = c->second.getNickname() + " " + c->second.getUsername() + " " + c->second.getHostname() + " * : " + c->second.getRealname();
                // c->second.response(str);
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
    // c->second.response(": End of /WHOIS list");
}