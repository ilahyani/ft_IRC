/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:11:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/27 18:54:30 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "server.hpp"

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

const int& client::getsocket() {
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

std::string client::get_format() {
    return getNickname() + "!" + getUsername() + "@" + getHostname() + " ";
}

void client::response(std::string str) {
    print(":" + get_format() + str);
}

void client::responsefromServer(std::string str) {
    print(":" + getHostname() + " " + str);
}

void client::print(std::string str) {
    std::string buff = str + "\n";
    if (send(_socket, buff.c_str(), buff.length(), 0) < 0)
        throw std::runtime_error("An error occurred while attempting to send a message to the client.\n");
}

void client::welcome(std::string dt) {
    if (isGuest && !getNickname().empty() && !getRealname().empty() && !getUsername().empty())
    {
        isGuest = false;
        isRegistered = true;
        responsefromServer(RPL_WELCOME(getNickname(), "IRC", getUsername(), getHostname()));   
        responsefromServer(RPL_YOURHOST(getNickname(), getHostname()));
        responsefromServer(RPL_CREATED(getNickname(), dt));
        responsefromServer(RPL_MOTD(getNickname(), " _____ _____   _____   _   _ ______ _________          ______  _____  _  __"));
        responsefromServer(RPL_MOTD(getNickname(), "|_   _|  __ \\ / ____| | \\ | |  ____|__   __\\ \\        / / __ \\|  __ \\| |/ /"));
        responsefromServer(RPL_MOTD(getNickname(), "  | | | |__) | |      |  \\| | |__     | |   \\ \\  /\\  / / |  | | |__) | ' / "));
        responsefromServer(RPL_MOTD(getNickname(), "  | | |  _  /| |      | . ` |  __|    | |    \\ \\/  \\/ /| |  | |  _  /|  <  "));
        responsefromServer(RPL_MOTD(getNickname(), " _| |_| | \\ \\| |____  | |\\  | |____   | |     \\  /\\  / | |__| | | \\ \\| . \\ "));
        responsefromServer(RPL_MOTD(getNickname(), "|_____|_|  \\_\\\\_____| |_| \\_|______|  |_|      \\/  \\/   \\____/|_|  \\_\\_|\\_\\"));
        responsefromServer(RPL_MOTD(getNickname(), " "));
        responsefromServer(RPL_ENDOFMOTD(getNickname()));
    }
}

void client::setRealname(std::string realname) { _realname = realname; }
void client::setUsername(std::string username) { _username = username; }
