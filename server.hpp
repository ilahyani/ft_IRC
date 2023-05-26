/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:51:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/26 08:23:14 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SERVER_HPP
#define SERVER_HPP

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
    struct sockaddr_in         _addr;
    std::vector<struct pollfd> _fdsVec;
    std::map<int, client>      _connectedClients;
    std::map<std::string, cmd> _cmdMap;
    std::vector<Channels>      _Channels;
    void                       _cmdMapinit();
    public:
        server();
        server(int port, std::string passwd);
        ~server();
        std::string getPasswd();
        void        setPasswd();
        int         getPort();
        std::vector<Channels>& getChannels();
        void        setPort();
        bool        startServ();
        void        addNewClient();
        void        checkConnectedClients();
        void        parseDataAndRespond(size_t pos);
        bool        HasError(std::vector<std::string> cmd);
        void        respondToClient(std::vector<std::string> cmd, std::map<int, client>::iterator client);
        bool        Check_client(int socket);
        client*     get_client(std::string nick);
        void        send_message_to_user(std::string user, std::string message, client client);
        void        join_to_channel(std::string channel, std::string key, client& client);
        Channels*   getChannel(std::string channel_name);
        void        send_message_to_channel(std::string user, std::string message, client client);
        void        sendToClient(int receiver, std::string nick_or_channel, std::string message, client sender, std::string cmd);
        void        responsefromServer(std::string str, client c);
        void        send_msg_to_all_users(Channels *ch, std::string msg, client c);
        void        send_to_clients(Channels *ch, client c, std::string cmd);
        std::pair<client, ROLE>* checkUserIsInChannel(client c, Channels *ch);

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


        /*function added by oqatim*/
        bool    checkUserIsInChannel1(client c, Channels *ch);
        void    sendToClient1(std::string receiver, std::string nick, std::string channel, client sender, std::string cmd);
        int     findClientByName(std::string nick, client client);
        client* findClientByName1(std::string nick);
        int     findChannelByName(std::string channel_name, client client);

        void    send_message_to_channel_n(std::string channel, std::string message, client c);
        void    send_message_to_user_n(std::string nick, std::string message, client c);
        bool    check_multichannel(const std::string& str);
        std::vector<std::string> ft_split_channels(std::string channels);
        bool isOperator(client c, Channels *ch);




        void whois(std::vector<std::string> params, std::map<int, client>::iterator c);
};

#endif