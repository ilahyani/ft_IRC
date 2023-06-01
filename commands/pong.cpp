/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:04:30 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/01 23:38:45 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::pong(std::vector<std::string> params, std::map<int, client>::iterator client) {

    if (params[1].empty())
    {
        client->second.ServertoClientPrefix(ERR_NOORIGIN(client->second.getNickname()));
        return ;
    }
    else if (params[1].compare(_hostAdr))
    {
        client->second.ServertoClientPrefix(ERR_NOSUCHSERVER(client->second.getNickname(), params[1]));
        return ;
    }
}