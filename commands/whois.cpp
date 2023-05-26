/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:08:08 by oqatim            #+#    #+#             */
/*   Updated: 2023/05/26 11:08:09 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::whois(std::vector<std::string> params, std::map<int, client>::iterator c)
{
    std::cout << "WHOIS command called\n";

    if(params.size() < 3)
    {
        if (check_multichannel(params[1]))
        {
            std::vector<std::string> Nick_list = ft_split_channels(params[1]);
            for (size_t i = 0; i < Nick_list.size(); i++)
            {
                int clientExist = findClientByName(Nick_list[i], c->second);
                if (clientExist == 1)
                {
                    client *client = findClientByName1(Nick_list[i]);
                    std::string str = client->getNickname() + " " + client->getUsername() + " " + client->getHostname() + " * : " + client->getRealname();
                    // std::cout << "fd ---" << client->getsocket() << "\n";
                    c->second.response(str);
                }
            }
        }
        else
        {
            int clientExist = findClientByName(params[1], c->second);
            if (clientExist == 1)
            {
                std::string str = c->second.getNickname() + " " + c->second.getUsername() + " " + c->second.getHostname() + " * : " + c->second.getRealname();
                c->second.response(str);
            }
        }
    }
    else
    {
        
    }
    c->second.response(": End of /WHOIS list");
}