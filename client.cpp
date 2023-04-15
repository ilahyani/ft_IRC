/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:11:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/15 06:30:07 by ilahyani         ###   ########.fr       */
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

const int&         client::getsocket() {
    return _socket;
}

const std::string& client::getNickname() {
    return _nickname;
}

const std::string& client::getRealname() {
    return _realname;
}

const std::string& client::getUsername() {
    return _username;
}

const std::string& client::getHostname() {
    return _hostname;
}

const std::string& client::getPasswd() {
    return _passwd;
}
