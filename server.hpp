/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:51:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/06/02 14:55:49 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"
#include "client.hpp"
#include "Channels.hpp"

class server {

    typedef void (server::*cmd)(std::vector<std::string> params, std::map<int, client>::iterator client);
    typedef std::map<int, client>::iterator client_iter;

    int                        _listenSocket;
    int                        _newSocket;
    char                       _buff[513];
    int                        _port;
    std::string                _passwd;
    std::string                _password_server;
    struct sockaddr_in         _addr;
    std::vector<struct pollfd> _fdsVec;
    std::map<int, client>      _connectedClients;
    std::map<std::string, cmd> _cmdMap;
    std::vector<Channels>      _Channels;
    void                       _cmdMapinit();
    std::string                _timeCreated;
    std::string                _hostAdr;
    public:
        server();
        server(int port, std::string passwd);
        ~server();
        std::string getPasswd();
        void setPasswd();
        int getPort();
        std::vector<Channels>& getChannels();
        void setPort();
        std::string getHostAdresse();
        std::string getTimeCreatedServer();
        bool startServ();
        void addNewClient();
        void checkConnectedClients();
        void parseDataAndRespond(size_t pos);
        bool HasError(std::vector<std::string> cmd);
        void respondToClient(std::vector<std::string> cmd, std::map<int, client>::iterator client);
        bool Check_client(int socket);
        client* get_client(std::string nick);
        void join_to_channel(std::string channel, std::string key, client& client);
        Channels* getChannel(std::string channel_name);
        void send_msg_to_all_users(Channels *ch, std::string msg, client c);
        void send_msg_to_clients_who_in_channel(Channels *ch, client c, std::string cmd);
        std::pair<client, ROLE>* checkUserIsInChannel(client c, Channels *ch);
        void deleteClient(client &c);
        void mode_plus(int &k, std::string &execMode, std::string &modeparams,std::string modex, Channels *ch, std::vector<std::string> params, std::map<int, client>::iterator c, client* cl);
        void mode_minus(int &k, std::string &execMode, std::string &modeparams,std::string modex, Channels *ch, std::vector<std::string> params, std::map<int, client>::iterator c, client* cl);
        ROLE checkRoleUserInChannel(client& c, Channels *ch);
        void send_to_all_in_channel(Channels *ch, client c, std::string cmd);
        void sendToClientById(int receiver, client sender, std::string message);
        std::string getClientsChannel(Channels *ch);

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
        void mode(std::vector<std::string> params, std::map<int, client>::iterator client);
        void bot(std::vector<std::string> params, std::map<int, client>::iterator client);
        void pong(std::vector<std::string> params, std::map<int, client>::iterator client);
        void oper(std::vector<std::string> params, std::map<int, client>::iterator client);
        void wallops(std::vector<std::string> params, std::map<int, client>::iterator client);
        void whois(std::vector<std::string> params, std::map<int, client>::iterator client);

};

