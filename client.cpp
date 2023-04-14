/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:11:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/13 10:30:04 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

client::client() {
    _isGuest = true;
    _isOpreator = false;
}

client:: client(int socket) : _socket(socket) {
    _isGuest = true;
    _isOpreator = false;
}

client::~client() {}