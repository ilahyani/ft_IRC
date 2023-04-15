/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:10:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/15 18:26:23 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server() {
    _cmdMapinit();
}

server::server(int port, std::string passwd) : _port(port), _passwd(passwd) {
    _cmdMapinit();
}

server::~server() {}

void    server::_cmdMapinit() {
    std::string cmd_strings[] = {"pass", "nick", "user", "join", "kick", "part", "notice", "privmsg", "quit", "topic"};
    cmd cmd_ptrs[] = {&server::pass, &server::nick, &server::user, &server::join, &server::kick, &server::part, &server::notice, &server::privmsg, &server::quit, &server::topic};
    int num_cmds = sizeof(cmd_ptrs) / sizeof(cmd);

    for (int i = 0; i < num_cmds; i++)
        _cmdMap.insert(std::make_pair(cmd_strings[i], cmd_ptrs[i]));
}

bool    server::startServ() {
    int ov = 1;
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
    std::cout << "Welcome to IRC Server\n";
    while (true) {
        int rv = poll(&_fdsVec[0], _fdsVec.size(), -1);
        std::cout << _fdsVec.size() - 1 << " connected clients\n";
        if (rv < 0)
            return false;
        if (_fdsVec[0].revents == POLLIN) {
            if (!addNewClient())
                return false;
        }
        else {
            if (!checkConnectedClients())
                return false;
        }
    }
    return true;
}

bool    server::addNewClient() {
    struct pollfd fd;
    socklen_t addr_len = sizeof(_addr);
    
    _newSocket = accept(_listenSocket, (struct sockaddr *)&_addr, &addr_len);
    if (_newSocket < 0) {
        std::cerr << "Failed to accept connection\n";
        return false;
    }
    std::cout << "Connection Accepted\n";
    fd.fd = _newSocket;
    fd.events = POLLIN;
    _fdsVec.push_back(fd);
    client newClient(_newSocket);
    _connectedClients.insert(std::make_pair(_newSocket, newClient));
    return true;
}

bool    server::checkConnectedClients() {
    int recvBytes;
    std::vector<std::string> cmd;

    for (size_t i = 1; i < _fdsVec.size(); i++) {
        memset(_buff, 0, sizeof(_buff));
        recvBytes = recv(_fdsVec[i].fd, _buff, sizeof(_buff), 0);
        if (recvBytes == -1) {
            std::cerr << "Unexpected Error! Closing connection with "
                << (_connectedClients.at(_fdsVec.at(i).fd)._isGuest ? "guest"
                : _connectedClients.at(_fdsVec.at(i).fd).getHostname())
                << std::endl;
            _connectedClients.erase(_fdsVec.at(i).fd);
            close(_fdsVec.at(i).fd);
            _fdsVec.erase(_fdsVec.begin() + i);
            i--;
        }
        if (recvBytes == 0) {
            if (_connectedClients.at(_fdsVec.at(i).fd)._isGuest)
                std::cout << "Guest client left the server\n";
            else
                std::cout << _connectedClients.at(_fdsVec.at(i).fd).getNickname() << " left the server\n";
            _connectedClients.erase(_fdsVec.at(i).fd);
            close(_fdsVec.at(i).fd);
            _fdsVec.erase(_fdsVec.begin() + i);
        }
        else {
            if (!parseReceivedData(i))
                return false;
            //respondToClient();
        }
    }
    return true;
}
   
bool    server::parseReceivedData(size_t pos) {
    std::vector<std::string>    cmdVec;
    std::string                 msg(_buff);
    size_t                      msgEnd;
    char                        *token;
    char                        str[512];

    msgEnd = msg.find_first_of("\r\n");
    if (msgEnd == std::string::npos)
        _connectedClients.at(_fdsVec.at(pos).fd)._clientBuff += msg;
    else {
        _connectedClients.at(_fdsVec.at(pos).fd)._clientBuff += msg.substr(0, msgEnd);
        std::cout << _connectedClients.at(_fdsVec.at(pos).fd)._clientBuff << "\n";
        std::strcpy(str, _connectedClients.at(_fdsVec.at(pos).fd)._clientBuff.c_str());
        token = std::strtok(str, " ");
        while (token != NULL) {
            cmdVec.push_back(token);
            token = std::strtok(NULL, " ");
        }
        _connectedClients.at(_fdsVec.at(pos).fd)._clientBuff.clear();
        if (!HasError(cmdVec))
            respondToClient(cmdVec, _connectedClients.find(_fdsVec.at(pos).fd));
    }
    return true;
}

/* Clients SHOULD NOT use a prefix when sending a
   message; if they use one, the only valid prefix is the registered
   nickname associated with the client. */

bool    server::HasError(std::vector<std::string> cmdVec) {
    bool hasPrefix = false;

    if (cmdVec[0][0] == ':')
        hasPrefix = true;
    if ((hasPrefix && cmdVec.size() < 3 )|| (!hasPrefix && cmdVec.size() < 2))
        return std::cerr << "Error: Missing command or arguments\n", true;
    if ((hasPrefix && cmdVec.size() > 17) || (!hasPrefix && cmdVec.size() > 16))
        return std::cerr << "Error: Too many arguments\n", true;
    //check if commands and args are valid
    //command to lower
    //prefix in server-client communication is useless, maybe just remove it?
    return false;
}

void    server::respondToClient(std::vector<std::string> cmdVec, std::map<int, client>::iterator client) {
    std::map<std::string, cmd>::iterator cmd_it;

    cmd_it = _cmdMap.find(cmdVec[0]);
    if (!client->second._isGuest) {
        if (cmd_it != _cmdMap.end())
            (this->*(cmd_it->second))(cmdVec, client);
        else
            std::cerr << "Error: unknown command\n";
    }
}