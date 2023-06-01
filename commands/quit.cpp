/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:31:02 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/01 23:44:35 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::quit(std::vector<std::string> params, std::map<int, client>::iterator cl) {

    std::string msg_quit;
    if (params.size() == 2)
        msg_quit = params[1];
    else 
        msg_quit = cl->second.getNickname();

    std::vector<Channels>::iterator it_channels = _Channels.begin();
    while (it_channels != _Channels.end())
    {
        if (checkUserIsInChannel(cl->second, &*it_channels))
        {
            send_msg_to_clients_who_in_channel(&*it_channels, cl->second, "QUIT :Quit: " + msg_quit);
            it_channels->removeMember(cl->second);
        }
        it_channels++;
    }
    
    cl->second.print("ERROR :Closing Link: " + cl->second.getServerIp() + " (Quit: " + msg_quit + ")");

    std::map<int, client>::iterator it_client = _connectedClients.begin();
    while (it_client != _connectedClients.end())
    {
        if (cl->first == it_client->first)
            _connectedClients.erase(it_client);
        it_client++;
    }

    close(cl->second.getsocket());
}