/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 08:32:30 by ilahyani          #+#    #+#             */
/*   Updated: 2023/06/02 15:58:23 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"
#include "replies_errors.hpp"

class client {
    int		    _socket;
    std::string _passwd;
    std::string _username;
    std::string _realname;
    std::string _nickname;
    std::string _hostip;
    std::string _serverip;
    public:
        std::time_t _time;
        bool isOpreator;
        bool isInvisible;
        bool isGuest;
        bool isRegistered;
        bool loggedIn;
        bool wallops;
        std::string	clientBuff;
        
        client();
        ~client();
        client(int _socket);
        const int& getsocket();
        const std::string& getNickname();
        const std::string& getRealname();
        const std::string& getUsername();
        const std::string& getServerIp();
        const std::string& getPasswd();
        const std::string& getHostIp();
        const std::string getJoiningTime();
        void setServerIp(std::string);
        void setNickname(std::string);
        void setRealname(std::string);
        void setUsername(std::string);
        void setHostIp(std::string);
        void setJoiningTime(std::time_t t);
        void print(std::string str);
        std::string getPrefixClient();
        void ClienttoClientPrefix(std::string str);
        void ServertoClientPrefix(std::string str);
        void welcome(std::string dateCreated);
};
