/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:41:58 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/02 18:13:53 by ilahyani         ###   ########.fr       */
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
        if (send(_newSocket, "Please register to the server using NICK and USER commands\n", 60, 0) < 0)
            throw std::runtime_error("An error occurred while attempting to send a message to the client.\n");
    }
}