/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:10:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/25 19:04:05 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void server::_cmdMapinit() {
    std::string cmd_strings[] = {"pass", "nick", "user", "join", "kick", "part", "notice", "privmsg", "quit", "topic", "names", "list", "invite", "mode", "bot"};
    cmd cmd_ptrs[] = {&server::pass, &server::nick, &server::user, &server::join, &server::kick, &server::part, &server::notice, &server::privmsg, &server::quit, &server::topic, &server::names, &server::list, &server::invite, &server::mode, &server::bot};
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
    if (bind(_listenSocket, (struct sockaddr *)&_addr, sizeof(_addr))) //reinterpret cast<>
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
    std::cout << "Connection Accepted\nPlease Login to the server using the PASS command\n";
    
    fd.fd = _newSocket;
    fd.events = POLLIN;
    _fdsVec.push_back(fd);
    client newClient(_newSocket);
    newClient.setHostname(inet_ntoa(_addr.sin_addr));
    _connectedClients.insert(std::make_pair(_newSocket, newClient));
}

void    server::checkConnectedClients() {
    int recvBytes;

    for (size_t i = 1; i < _fdsVec.size(); i++) {
        if (_fdsVec.at(i).revents == POLLIN) {
            memset(_buff, 0, sizeof(_buff));
            recvBytes = recv(_fdsVec[i].fd, _buff, sizeof(_buff), 0);
            if (recvBytes == -1) {
                std::cerr << "Unexpected Error! Closing connection with "
                    << (_connectedClients.at(_fdsVec.at(i).fd).isGuest ? "guest"
                    : _connectedClients.at(_fdsVec.at(i).fd).getNickname())
                    << std::endl;
                _connectedClients.erase(_fdsVec.at(i).fd);
                close(_fdsVec.at(i).fd);
                _fdsVec.erase(_fdsVec.begin() + i);
                i--;
            }
            if (recvBytes == 0) {
                if (_connectedClients.at(_fdsVec.at(i).fd).isGuest)
                    std::cout << "Guest client left the server\n";
                else
                    std::cout << _connectedClients.at(_fdsVec.at(i).fd).getNickname() << " left the server\n";
                _connectedClients.erase(_fdsVec.at(i).fd);
                close(_fdsVec.at(i).fd);
                _fdsVec.erase(_fdsVec.begin() + i);
            }
            else
                parseDataAndRespond(i);
        }   
    }
}

// int check_next_space(std::string token, int i)
// {
//     int j = 0;
//     while (j < (int)token.size())
//     {
//         if (token[j] == ' ' || token[j] == '\0')
//             return (i);
//         j++;
//         i++;
//     }    
//     return (i);
// }

void server::parseDataAndRespond(size_t pos) {
    std::vector<std::string>    cmdVec;
    std::string                 msg(_buff);
    size_t                      msgEnd;
    // char                        *token;
    char                        str[512];

    std::string     str1;
    std::string     cm;

    msgEnd = msg.find_first_of("\r\n");
    if (msgEnd == std::string::npos)
        _connectedClients.at(_fdsVec.at(pos).fd).clientBuff += msg;
    else {
        _connectedClients.at(_fdsVec.at(pos).fd).clientBuff += msg.substr(0, msgEnd);
        std::strcpy(str, _connectedClients.at(_fdsVec.at(pos).fd).clientBuff.c_str());

        str1 = _connectedClients.at(_fdsVec.at(pos).fd).clientBuff;

        int i = 0;
        int j = 0;
        while (i < (int)str1.size())
        {
            if (str1[i] == ' ')
                i++;
            if (str1[i] == ':')
            {
                j = 0;
                i++;
                while (str1[i] && j < (int)str1.size())
                    str[j++] = str1[i++];
                str[j] = '\0';
                // if (std::strlen(str) < 1)
                //     cmdVec.push_back(":");
                cmdVec.push_back(str);
                break;
            }
            j = 0;
            while (str1[i] && (str1[i] != ' '))
                str[j++] = str1[i++];
            str[j] = '\0';
            cmdVec.push_back(str);
            i++;
        }
        
        // token = std::strtok(str, " ");
        // if (token && token[0] == ':')
        //     token = std::strtok(NULL, " ");
        // while (token != NULL) {
        //     cmdVec.push_back(token);
        //     token = std::strtok(NULL, " ");
        // }
        if (!cmdVec.empty())
            std::transform(cmdVec[0].begin(), cmdVec[0].end(), cmdVec[0].begin(), ::tolower);
        _connectedClients.at(_fdsVec.at(pos).fd).clientBuff.clear();
        if (!HasError(cmdVec))
            respondToClient(cmdVec, _connectedClients.find(_fdsVec.at(pos).fd));
    }
}

bool    server::HasError(std::vector<std::string> cmdVec) {
    // https://www.rfc-editor.org/rfc/rfc2812#section-2
    
    for (size_t i = 0; i < cmdVec.size(); i++) {
        std::cout << cmdVec[i] << " ";
        if (i == cmdVec.size() - 1)
            std::cout << std::endl;
    }
    return false;
}

void server::respondToClient(std::vector<std::string> cmdVec, std::map<int, client>::iterator client) {
    std::map<std::string, cmd>::iterator cmd_it;
    std::string command;

    if (cmdVec.size() > 0)
        command = cmdVec[0];
    cmd_it = _cmdMap.find(command);
    if (client->second.loggedIn) {
        if (!client->second.isGuest) {
            if (cmd_it != _cmdMap.end())
                (this->*(cmd_it->second))(cmdVec, client);
            else
                client->second.response(ERR_UNKNOWNCOMMAND(client->second.getNickname(), command));
        }
        else {
            if (cmd_it != _cmdMap.end() && (!cmd_it->first.compare("nick") || !cmd_it->first.compare("user"))) 
            {
                if(!cmd_it->first.compare("nick"))
                    server::nick(cmdVec, client);
                else if (!cmd_it->first.compare("user"))
                    server::user(cmdVec, client);
            }
            else
                std::cout << "Please register to the server using NICK and USER commands\n";
        }
    }
    else {
        if (cmd_it != _cmdMap.end() && !cmd_it->first.compare("pass"))
            server::pass(cmdVec, client);
        else
            std::cout << "Please Login to the server using the PASS command\n";
    }
}

std::string server::getPasswd(){
    return _passwd;
}

std::vector<Channels>& server::getChannels(){
    return _Channels;
}

bool server::Check_client(int socket)
{   
    std::map<int, client>::iterator it = _connectedClients.begin();
    for (; it != _connectedClients.end(); it++)
    {
        if (socket == it->second.getsocket())
            return true;
    }
    return false;
}

client* server::get_client(std::string nick)
{   
    std::map<int, client>::iterator it = _connectedClients.begin();
    for (; it != _connectedClients.end(); it++)
    {
        if (nick == it->second.getNickname())
            return &it->second;
    }
    return NULL;
}

Channels* server::getChannel(std::string channel_name)
{
    std::vector<Channels>::iterator it = _Channels.begin();
    for (; it != _Channels.end(); it++)
    {
        if (channel_name == it->getName())
            return &(*it);
    }
    return NULL;
}

void    server::sendToClient(int receiver, std::string nick_or_channel, std::string message, client sender, std::string cmd)
{
    std::string msg = ":" + sender.get_format() + cmd + " " + nick_or_channel + " :" + message + "\n";
    if(Check_client(receiver))
    {
        if (send(receiver, msg.c_str(), msg.length(), 0) < 0)
            throw std::runtime_error("An error occurred while attempting to send a message to the client.\n");
    }
    msg.clear();
}

std::pair<client, ROLE>* server::checkUserIsInChannel(client c, Channels *ch)
{
    std::vector<std::pair<client, ROLE> > Members = ch->getMembers();
    std::vector<std::pair<client, ROLE> >::iterator it = Members.begin();

    while (it != Members.end())
    {
        if (it->first.getsocket() == c.getsocket())
            return &*it;
        it++;
    }
    return NULL;
}

void server::send_to_clients(Channels *ch, client c, std::string cmd)
{
    int i = 0;
    std::vector<std::pair<client, ROLE> > clients = ch->getMembers();
    std::string message = ":" + c.get_format() + cmd + "\n";
    while (i < (int)clients.size())
    {
        send(clients[i].first.getsocket(), message.c_str(), message.length(), 0);
        i++;
    }
}