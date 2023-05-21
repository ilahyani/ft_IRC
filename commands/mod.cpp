/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 01:41:20 by oqatim            #+#    #+#             */
/*   Updated: 2023/05/19 01:41:24 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::mod(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "MOD command called\n";
}