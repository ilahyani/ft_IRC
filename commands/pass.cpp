/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:41:58 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/04/29 13:42:02 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::pass(std::vector<std::string> params, std::map<int, client>::iterator client) {
    if (!client->second.loggedIn)
    {
        if (params.size() == 2 && params[1] == server::getPasswd())
        {
            client->second.loggedIn = true;
            std::cout << "Success !\n";
        }
        else 
            std::cout << "Wrong password, try again !\n";
    }
}