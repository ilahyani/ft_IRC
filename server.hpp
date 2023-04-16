/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:51:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/16 18:25:13 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"
#include "client.hpp"

class server {

    typedef bool (server::*cmd)(std::vector<std::string> params, std::map<int, client>::iterator client);

    int                        _listenSocket;
    int                        _newSocket;
    char                       _buff[512];
    int                        _port;
    std::string                _passwd;
    struct sockaddr_in         _addr;
    std::vector<struct pollfd> _fdsVec;
    std::map<int, client>      _connectedClients;
    std::map<std::string, cmd> _cmdMap;
    void                       _cmdMapinit();
    public:
        server();
        server(int port, std::string passwd);
        ~server();
        std::string getPasswd();
        void setPasswd();
        int getPort();
        void setPort();
        bool startServ();
        void addNewClient();
        void checkConnectedClients();
        void parseDataAndRespond(size_t pos);
        bool HasError(std::vector<std::string> cmd);
        void respondToClient(std::vector<std::string> cmd, std::map<int, client>::iterator client);
        
        /* COMMANDS (make void later)*/
        
        bool pass(std::vector<std::string> params, std::map<int, client>::iterator client);
        bool nick(std::vector<std::string> params, std::map<int, client>::iterator client);
        bool user(std::vector<std::string> params, std::map<int, client>::iterator client);
        bool join(std::vector<std::string> params, std::map<int, client>::iterator client);
        bool kick(std::vector<std::string> params, std::map<int, client>::iterator client);
        bool part(std::vector<std::string> params, std::map<int, client>::iterator client);
        bool notice(std::vector<std::string> params, std::map<int, client>::iterator client);
        bool privmsg(std::vector<std::string> params, std::map<int, client>::iterator client);
        bool quit(std::vector<std::string> params, std::map<int, client>::iterator client);
        bool topic(std::vector<std::string> params, std::map<int, client>::iterator client);
};

#endif