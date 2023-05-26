/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:53:41 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/26 08:22:21 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

// bool isMember(const client& client) {
//     for (size_t i = 0; i < _Members.size(); i++) {
//         if (_Members[i].first == client && _Members[i].second == MEMBER) {
//             return true;
//         }
//     }
//     return false;
// }



void server::kick(std::vector<std::string> params, std::map<int, client>::iterator c)
{
    std::cout << "KCIK command called\n";
    
    (void)params;
    (void)c;

    // int channelExist = findChannelByName(params[1], c->second);
    // int clientExist = findClientByName(params[2]);
    // if (channelExist == 1)
    // {
    //     Channels *ch = getChannel(params[1]);
    //     if (clientExist == 1)
    //     {
    //         client *receiver = findClientByName1(params[2]);
    //         if (checkUserIsInChannel1(*receiver, ch))
    //         {
    //             if (isOperator(c->second, ch))
    //             {    
                     
    //             }
    //             else
    //             {
    //                 std::cout << "this nickname is not owner in this channel " << std::endl;
    //             }
    //         }
            
    //     }
    // }
}