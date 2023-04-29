/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:31:57 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/04/29 13:32:16 by kid-bouh         ###   ########.fr       */
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

    if (params.size() == 2 && client->second.getNickname().empty() )
    {
        if (isNicknameValid(params[1]))
        {
            client->second.setNickname(params[1]);
            std::cout << "The Nickname (" << client->second.getNickname() << ") has been added \n";
        }
        else 
           std::cout << "Invalid characters in nickname, Try Again !"; 
    }
    else if (params.size() == 2 && !client->second.getNickname().empty())
    {
        std::string old_nick;

        old_nick = client->second.getNickname();
        if (isNicknameValid(params[1]))
        {
            client->second.setNickname(params[1]);
            std::cout << "The Nickname (" << old_nick << ") has been changed to " << client->second.getNickname() << '\n';
        }
        else 
           std::cout << "Invalid characters in nickname, Try Again !"; 
    }
}