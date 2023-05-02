/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 08:32:30 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/02 23:32:41 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "irc.hpp"

#define ERR_NEEDMOREPARAMS(src)       "461 " + src + " :Not enough parameters"
#define ERR_PASSWDMISMATCH(src)       "464 " + src + " :Incorrect password"
#define ERR_UNKNOWNCOMMAND(src, cmd)  "421 " + src + " " + cmd + " :Unknown command"
#define ERR_ERRONEUSNICKNAME(src)     "432 " + src + " :Erroneus nickname"
#define ERR_NICKNAMEINUSE(src)        "433 " + src + " :Nickname is already in use"
#define ERR_ALREADYREGISTRED(src)     "462 " + src + " :You may not reregister"
#define IRC_WELCOME(src)              "001 " + src + " :Welcome to IRC Network"

class client {
    int				        _socket;
    std::string		        _passwd;
    std::string		        _hostname;
    std::string		        _nickname;
    std::string		        _username;
    std::string		        _realname;
    public:
        bool            isOpreator;
        bool            isGuest;
        bool            isRegistered;
        bool            loggedIn;
        std::string		clientBuff;
        
        client();
        ~client();
        client(int _socket);
        const int&         getsocket();
        const std::string& getNickname();
        const std::string& getRealname();
        const std::string& getUsername();
        const std::string& getHostname();
        const std::string& getPasswd();
        void               setHostname(std::string);
        void               setNickname(std::string);
        void               setRealname(std::string);
        void               setUsername(std::string);
        void               print(std::string str);
        void               response(std::string str);
        std::string        get_format();
        void               welcome();

};

#endif