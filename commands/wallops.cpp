/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallops.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 00:45:04 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/30 00:49:56 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::wallops(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void) params;
    (void) client;
    std::cout << "wallops command\n" ;
}