/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:41:58 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/01 23:41:01 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::pass(std::vector<std::string> params, std::map<int, client>::iterator client) {
    if (!client->second.loggedIn)
    {
        if (params.size() < 2)
        {
            client->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(client->second.getNickname()));
            return ;
        }
        if (params[1] != server::getPasswd() || params.size() != 2)
        {
            client->second.ServertoClientPrefix(ERR_PASSWDMISMATCH(client->second.getNickname()));
            return ;   
        }
        client->second.loggedIn = true;
    }
}