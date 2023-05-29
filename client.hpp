/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 08:32:30 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/29 22:33:20 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"
#include "replies_errors.hpp"

class client {
    int		    _socket;
    std::string _passwd;
    std::string _hostname;
    std::string _username;
    std::string _realname;
    std::string _nickname;
    std::string _hostip;
    public:
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
        const std::string& getHostname();
        const std::string& getPasswd();
        const std::string& getHostIp();
        void setHostname(std::string);
        void setNickname(std::string);
        void setRealname(std::string);
        void setUsername(std::string);
        void setHostIp(std::string);
        void print(std::string str);
        void response(std::string str);
        std::string get_format();
        void responsefromServer(std::string str);
        void welcome(std::string dateCreated);
};
