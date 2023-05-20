/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:06:40 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/20 00:50:18 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::mode(std::vector<std::string> params, std::map<int, client>::iterator client) {
    if (params.size() < 3)
    {
        client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }
    
    std::string channel = params[1];
    std::string modes = params[2];

    if (modes[0] == '+')
    {
        int i = 1;
        char out[10];
        int j = 0;
        out[j++] = '+';
        while (i < (int)modes.size())
        {
            if (modes[i] == 'i')
            {
                client->second.response("+i");
            }
            else if (modes[i] == 't')
            {
                client->second.response("+t");
            }
            else if (modes[i] == 'k')
            {
                
                out[j++] = 'k';
            }
            else if (modes[i] == 'o')
            {
                client->second.response("+o");
            }
            else if (modes[i] == 'l')
            {
                client->second.response("+l");
            }
            else
            {
                client->second.response(ERR_UNKNOWNMODE(client->second.getNickname(), modes[i]));
            }
            i++;
        }
    }
    else if (modes[0] == '-')
    {
        int i = 1;
        while (i < (int)modes.size())
        {
            if (modes[i] == 'i')
            {
                client->second.response("-i");
            }
            else if (modes[i] == 't')
            {
                client->second.response("-t");
            }
            else if (modes[i] == 'k')
            {
                client->second.response("-k");
            }
            else if (modes[i] == 'o')
            {
                client->second.response("-o");
            }
            else if (modes[i] == 'l')
            {
                client->second.response("-l");
            }
            else
            {
                client->second.response(ERR_UNKNOWNMODE(client->second.getNickname(), modes[i]));
            }
            i++;
        }
    }
    else 
    {
        client->second.response("ERROR");
    }
    

}