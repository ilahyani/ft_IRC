/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 08:32:30 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/07 00:53:06 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "irc.hpp"

#define ERR_NEEDMOREPARAMS(nick)       "461 " + nick + " :Not enough parameters"
#define ERR_PASSWDMISMATCH(nick)       "464 " + nick + " :Incorrect password"
#define ERR_UNKNOWNCOMMAND(nick, cmd)  "421 " + nick + " " + cmd + " :Unknown command"
#define ERR_ERRONEUSNICKNAME(nick)     "432 " + nick + " :Erroneus nickname"
#define ERR_NICKNAMEINUSE(nick)        "433 " + nick + " :Nickname is already in use"
#define ERR_ALREADYREGISTRED(nick)     "462 " + nick + " :You may not reregister"
#define IRC_WELCOME(nick)              "001 " + nick + " :Welcome to IRC Network"

#define ERR_CANNOTSENDTOCHAN(nick)     "404 " + nick + " :Cannot send to channel"
#define ERR_NOTEXTTOSEND(nick)         "412 " + nick + " :No text to send"
#define ERR_NOSUCHNICK(nick)           "401 " + nick + " :No such nick/channel"
#define ERR_BADCHANNAME(nick)          "479 " + nick + " :Invalid channel name"
#define ERR_BADCHANNELKEY(nick)        "475 " + nick + " :Cannot join channel (+k)"
#define ERR_USERONCHANNEL(nick, ch)    "443 " + nick + " " + ch + " :is already on channel"

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