/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:28:06 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/21 01:28:07 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::invite(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "INVITE command called\n";
}