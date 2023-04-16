/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:10:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/16 15:00:34 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void server::_cmdMapinit() {
    std::string cmd_strings[] = {"pass", "nick", "user", "join", "kick", "part", "notice", "privmsg", "quit", "topic"};
    cmd cmd_ptrs[] = {&server::pass, &server::nick, &server::user, &server::join, &server::kick, &server::part, &server::notice, &server::privmsg, &server::quit, &server::topic};
    int num_cmds = sizeof(cmd_ptrs) / sizeof(cmd);

    for (int i = 0; i < num_cmds; i++)
        _cmdMap.insert(std::make_pair(cmd_strings[i], cmd_ptrs[i]));
}

server::server() {
    _cmdMapinit();
}

server::server(int port, std::string passwd) : _port(port), _passwd(passwd) {
    _cmdMapinit();
}

server::~server() {
}

bool server::startServ() {
    int ov = 1;
    struct pollfd fd;

    _listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_listenSocket < 0)
        return std::cerr << "Failed to create socket\n", false;

    if (setsockopt(_listenSocket, SOL_SOCKET, SO_REUSEADDR, &ov, sizeof(ov)) < 0
        || fcntl(_listenSocket, F_SETFL, O_NONBLOCK) < 0) {
            close (_listenSocket);
            return std::cerr << "Unexpected error\n", false;
    }
    std::vector<int> second (4,100);
    memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(_listenSocket, (struct sockaddr *)&_addr, sizeof(_addr)))
        return std::cerr << "Failed to bind socket, Port already in use\n", false;

    if (listen(_listenSocket, 32) < 0) {
        close (_listenSocket);
        return std::cerr << "Failed to listen()\n", false;
    }

    fd.fd = _listenSocket;
    fd.events = POLLIN;
    _fdsVec.push_back(fd);
    std::cout << "Welcome to IRC Server\n";
    while (true) {
        int rv = poll(&_fdsVec[0], _fdsVec.size(), -1);
        if (rv < 0)
            return std::cerr << "Poll() system call failed\n", false;

        if (_fdsVec[0].revents == POLLIN)
            addNewClient();
        else
            checkConnectedClients();
    }
    return true;
}

void server::addNewClient() {
    struct pollfd fd;
    socklen_t addr_len = sizeof(_addr);

    _newSocket = accept(_listenSocket, (struct sockaddr *)&_addr, &addr_len);
    if (_newSocket < 0) {
        std::cerr << "Failed to accept connection\n";
        return;
    }
    std::cout << "Connection Accepted\n";
    fd.fd = _newSocket;
    fd.events = POLLIN;
    _fdsVec.push_back(fd);
    client newClient(_newSocket);
    _connectedClients.insert(std::make_pair(_newSocket, newClient));
}


void    server::checkConnectedClients() {
    int recvBytes;
    std::vector<std::string> cmd;

    for (size_t i = 1; i < _fdsVec.size(); i++) {
        if (_fdsVec.at(i).revents == POLLIN) {
            memset(_buff, 0, sizeof(_buff));
            recvBytes = recv(_fdsVec[i].fd, _buff, sizeof(_buff), 0);
            if (recvBytes == -1) {
                std::cerr << "Unexpected Error! Closing connection with "
                    << (_connectedClients.at(_fdsVec.at(i).fd)._isGuest ? "guest"
                    : _connectedClients.at(_fdsVec.at(i).fd).getNickname())
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
            else
                parseReceivedData(i);
        }   
    }
}
   
void server::parseReceivedData(size_t pos) {
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
}

bool    server::HasError(std::vector<std::string> cmdVec) {
    // https://www.rfc-editor.org/rfc/rfc2812#section-2
    (void)cmdVec;
    return false;
}

void server::respondToClient(std::vector<std::string> cmdVec, std::map<int, client>::iterator client) {
    std::map<std::string, cmd>::iterator cmd_it;
    std::string command;

    if (cmdVec.size() > 0)
        command = (cmdVec[0][0] == ':' ? cmdVec[1] : cmdVec[0]);
    cmd_it = _cmdMap.find(command);
    if (client->second._loggedIn) {
        if (!client->second._isGuest) {
            if (cmd_it != _cmdMap.end())
                (this->*(cmd_it->second))(cmdVec, client);
            else
                std::cerr << "Error: unknown command\n";
        }
        else {
            if (cmd_it != _cmdMap.end() && !cmd_it->first.compare("nick")) {
                server::nick(cmdVec, client);
                client->second._isGuest = false;
            }
            else if (cmd_it != _cmdMap.end() && !cmd_it->first.compare("user")){
                server::user(cmdVec, client);
                client->second._isGuest = false;
            }
            else
                std::cout << "Please register\n";
        }
    }
    else {
        if (cmd_it != _cmdMap.end() && !cmd_it->first.compare("pass")) {
            client->second._loggedIn = true;
            server::pass(cmdVec, client);
        }
        else
            std::cout << "Please Login to the server\n";
    }
}
