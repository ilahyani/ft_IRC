/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:51:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/02 18:16:01 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"
#include "client.hpp"

class server {

    typedef void (server::*cmd)(std::vector<std::string> params, std::map<int, client>::iterator client);
    typedef std::map<int, client>::iterator client_iter;

    int                        _listenSocket;
    int                        _newSocket;
    char                       _buff[513];
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

        bool Check_client(std::string Nick);
        
        /* COMMANDS */
        
        void pass(std::vector<std::string> params, std::map<int, client>::iterator client);
        void nick(std::vector<std::string> params, std::map<int, client>::iterator client);
        void user(std::vector<std::string> params, std::map<int, client>::iterator client);
        void join(std::vector<std::string> params, std::map<int, client>::iterator client);
        void kick(std::vector<std::string> params, std::map<int, client>::iterator client);
        void part(std::vector<std::string> params, std::map<int, client>::iterator client);
        void notice(std::vector<std::string> params, std::map<int, client>::iterator client);
        void privmsg(std::vector<std::string> params, std::map<int, client>::iterator client);
        void quit(std::vector<std::string> params, std::map<int, client>::iterator client);
        void topic(std::vector<std::string> params, std::map<int, client>::iterator client);
        void names(std::vector<std::string> params, std::map<int, client>::iterator client);
        void list(std::vector<std::string> params, std::map<int, client>::iterator client);
        void invite(std::vector<std::string> params, std::map<int, client>::iterator client);
        void mod(std::vector<std::string> params, std::map<int, client>::iterator client);
        void bot(std::vector<std::string> params, std::map<int, client>::iterator client);
};

#endif