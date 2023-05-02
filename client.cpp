/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:11:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/02 23:34:54 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

client::client() {
    isGuest = true;
    isOpreator = false;
    loggedIn = false;
    isRegistered = false;
}

client:: client(int socket) : _socket(socket) {
    isGuest = true;
    isOpreator = false;
    loggedIn = false;
    isRegistered = false;
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

void client::setNickname(std::string nickname) {
    _nickname = nickname;
}

void client::setHostname(std::string hostName) {
   _hostname = hostName;
}

std::string client::get_format()
{
    return client::getNickname() + "!" + client::getUsername() + "@" + client::getHostname();
}

void client::response(std::string str)
{
    print(":" + get_format() + str);
}

void client::print(std::string str)
{
    std::string buff = str + "\n";
    if (send(_socket, buff.c_str(), buff.length(), 0) < 0)
        throw std::runtime_error("An error occurred while attempting to send a message to the client.\n");
}

void client::welcome()
{
    if (isGuest && !client::getNickname().empty() && !client::getRealname().empty() && !client::getUsername().empty())
    {
        client::isGuest = false;
        client::isRegistered = true;
        client::response(IRC_WELCOME(client::getNickname()));
    }
}

void client::setRealname(std::string realname) { _realname = realname; }
void client::setUsername(std::string username) { _username = username; }