/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:06:09 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/02 18:16:39 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

bool isNicknameValid(std::string nick) {

    std::string invalidChars = " ,:;-?!&%\\/()[]{}\"'~^$#*";

    if (nick[0] == '.')
        return false;

    for (int i = 0; i < (int)nick.length(); i++)
    {
        if (invalidChars.find(nick[i]) != std::string::npos)
            return false;
    }
    return true;
}

void server::nick(std::vector<std::string> params, std::map<int, client>::iterator client) {

    if (params.size() != 2)
    {
        client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }

    if (!isNicknameValid(params[1]))
    {
        client->second.response(ERR_ERRONEUSNICKNAME(client->second.getNickname()));
        return ;
    }
    
    if (server::Check_client(params[1]))
    {
        client->second.response(ERR_NICKNAMEINUSE(client->second.getNickname()));
        return ;
    }

    client->second.setNickname(params[1]);

    client->second.welcome();
}