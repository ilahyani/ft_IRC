/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:53:41 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/25 10:04:18 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

bool isOperator(client c, Channels *ch)
{
    // std::vector<std::pair<client, ROLE> > _Members = ch->getMembers();

    // for (size_t i = 0; i < _Members.size(); i++) {
    //     if (_Members[i].first == client && _Members[i].second == OPERATOR) {
    //         return true;
    //     }
    // }
    // return false;



    std::vector<std::pair<client, ROLE> > Members = ch->getMembers();
    // std::vector<std::pair<client, ROLE> >::iterator it = Members.begin();

    // while (it != Members.end())
    for (size_t i = 0; i < Members.size(); i++) 
    {
        if (Members[i].first.getsocket() == c.getsocket() && Members[i].second == OPERATOR)
            return true;
        // it++;
    }
    return false;
}

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