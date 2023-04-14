/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:10:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/13 18:38:00 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server() {}

server::~server() {}

bool    server::startServ() {
    int ov = 1;
    bool end_serv = false;
    struct pollfd fd;

    _port = 12345;
    _listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_listenSocket < 0)
        return false;
    if (setsockopt(_listenSocket, SOL_SOCKET, SO_REUSEADDR, &ov, sizeof(ov)) < 0
        || fcntl(_listenSocket, F_SETFL, O_NONBLOCK) < 0) {
            close (_listenSocket);
            return false;
    }
    std::vector<int> second (4,100);
    memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(_listenSocket, (struct sockaddr *)&_addr, sizeof(_addr))
        || listen(_listenSocket, 10) < 0) {
            close (_listenSocket);
            return false;
    }
    fd.fd = _listenSocket;
    fd.events = POLLIN;
    _fdsVec.push_back(fd);
    while (true) {
        std::cout << "Waiting on incoming connections...\n";
        int rv = poll(&_fdsVec[0], _fdsVec.size(), -1);
        std::cout << _fdsVec.size() << "\n";
        if (rv < 0)
            return false;
        if (_fdsVec[0].revents == POLLIN) {
            socklen_t addr_len = sizeof(_addr);
            _newSocket = accept(_listenSocket, (struct sockaddr *)&_addr, &addr_len);
            if (_newSocket < 0) {
                std::cerr << "Failed to accept connection\n";
                return false;
            }
            std::cout << "Connection Accepted\n";
            fd.fd = _newSocket;
            // fd.events = POLLIN;
            _fdsVec.push_back(fd);
            std::map<int, client> newClient(_newSocket);
            _connectedClients.insert(std::make_pair(_newSocket, client));
        }
        else
            checkData();
    }
    return true;
}

void    server::checkData() {
    int recvBytes;

    for (size_t i = 1; i < _fdsVec.size(); i++) {
        recvBytes = recv(_fdsVec[i].fd, _buff, sizeof(_buff), 0);
        if (recvBytes > 0) {
            parseBuff();
            // if (_connectedClients.at(_fdsVec.at(i).fd)._isGuest) auth
            // else execCmd
        }
    }
}

void    server::parseBuff() {}