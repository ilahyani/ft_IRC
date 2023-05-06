/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:18:50 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/05 20:03:07 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::send_message_to_user(std::string user, std::string message, client client)
{
    if (user != get_client(user)->getNickname())
    {
        client.response(ERR_NOSUCHNICK(client.getNickname()));
        return ;
    }
    std::string msg = ":" + client.get_format() + " PRIVMSG " + get_client(user)->getNickname() + " :" + message + "\n";
    if (send(get_client(user)->getsocket(), msg.c_str(), msg.length(), 0) < 0)
            throw std::runtime_error("An error occurred while attempting to send a message to the client.\n");
}

void server::privmsg(std::vector<std::string> params, std::map<int, client>::iterator client) {

    (void) client;
    std::string message;

    if (params.size() < 3)
    {
        client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }
    if (params[2][0] != ':')
        return ;
    message = params[2].substr(1, params[2].size()) + " ";
    for (int i = 3; i < (int)params.size(); i++)
        message += params[i] + " ";

    send_message_to_user(params[1], message, client->second);
}