/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:06:09 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/26 16:54:24 by kid-bouh         ###   ########.fr       */
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

void server::nick(std::vector<std::string> params, std::map<int, client>::iterator cl) {

    if (params.size() != 2)
    {
        cl->second.response(ERR_NEEDMOREPARAMS(cl->second.getNickname()));
        return ;
    }

    if (!isNicknameValid(params[1]))
    {
        cl->second.response(ERR_ERRONEUSNICKNAME(cl->second.getNickname()));
        return ;
    }
    
    if (get_client(params[1]))
    {
        cl->second.response(ERR_NICKNAMEINUSE(cl->second.getNickname()));
        return ;
    }

    std::vector<Channels>::iterator it_chs = getChannels().begin();
    while (it_chs != getChannels().end())
    {
        std::vector<std::pair<client, ROLE> >::iterator it_m = it_chs->getMembers().begin();
        while (it_m != it_chs->getMembers().end())
        {
            if (it_m->first.getsocket() == cl->second.getsocket())
                it_m->first.setNickname(params[1]);
            it_m++;
        }
        it_chs++;
    }

    cl->second.setNickname(params[1]);
    cl->second.welcome(_timeCreated);
}