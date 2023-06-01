/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:55:55 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/01 23:38:45 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::oper(std::vector<std::string> params, std::map<int, client>::iterator client) {
    
    if (!client->second.isOpreator)
    {
        if (params.size() < 3)
        {
            client->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(client->second.getNickname()));
            return ;
        }
        
        if (params[2].compare(_password_server) || params[1].compare(client->second.getNickname()))
        {
            client->second.ServertoClientPrefix(ERR_PASSWDMISMATCH(client->second.getNickname()));
            return ;
        }
        client->second.ServertoClientPrefix(RPL_YOUREOPER(client->second.getNickname()));
        client->second.isOpreator = true;
    }
}