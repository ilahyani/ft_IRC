/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:05:23 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/26 16:54:10 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

bool isUsernameValid(std::string nick) {

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

bool isRealnameValid(std::string nick) {

    std::string invalidChars = ",:;_?!&%\\/()[]{}\"'~^$#*";

    if (nick[0] == '.')
        return false;

    for (int i = 0; i < (int)nick.length(); i++)
    {
        if (invalidChars.find(nick[i]) != std::string::npos)
            return false;
    }
    return true;
}

void server::user(std::vector<std::string> params, std::map<int, client>::iterator client) {

    std::string Realname;
    
    if (params.size() < 5)
    {
        client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }
    
    if (client->second.isRegistered)
    {
        client->second.response(ERR_ALREADYREGISTRED(client->second.getNickname()));
        return ;
    }

    client->second.setUsername(params[1]);
    client->second.setRealname(params[4]);
    client->second.welcome(_timeCreated);

}