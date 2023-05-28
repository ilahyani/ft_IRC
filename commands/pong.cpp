/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:04:30 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/28 19:07:20 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::pong(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void) params; 
    (void) client; 
    std::cout << "pong command\n";
}