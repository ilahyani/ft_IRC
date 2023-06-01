/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:31:07 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/06/01 23:53:46 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::notice(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "NOTICE command called\n";
}