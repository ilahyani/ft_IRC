/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:26:07 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/30 22:27:42 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::part(std::vector<std::string> params, std::map<int, client>::iterator client) {

    if (params.size() < 2)
    {
        client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }

    Channels *ch = getChannel(params[1]);
    if (!ch)
    {
        client->second.responsefromServer(ERR_NOSUCHCHANNEL(client->second.getNickname(), params[1]));
        return ;
    }

    if (!checkUserIsInChannel(client->second, ch))
    {
        client->second.responsefromServer(ERR_NOTONCHANNEL(client->second.getNickname(), params[1]));
        return ;
    }

    send_to_all_in_channel(ch, client->second, "PART " + ch->getName());
    ch->removeMember(client->second);
}