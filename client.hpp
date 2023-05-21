/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 08:32:30 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/20 11:51:25 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "irc.hpp"

#define ERR_NORECIPIENT(nick, cmd)          "411 " + nick + " :No recipient given " + cmd
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

#define RPL_NAMREPLY(nick, ch, members) "353 " + nick + " = " + ch + " :" + members
#define RPL_ENDOFNAMES(nick, ch)        "366 " + nick + " " + ch + " :End of NAMES list"

#define ERR_NOSUCHCHANNEL(nick, ch)      "403 " + nick + " " + ch + " :No such channel"
#define RPL_TOPIC(nick, ch, topic)       "332 " + nick + " " + ch + " :" + topic
#define ERR_NOTONCHANNEL(nick, ch)       "442 " + nick + " " + ch + " :You're not on that channel"
#define RPL_NOTOPIC(nick, ch)            "331 " + nick + " " + ch + " :No topic is set"

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
        void               responsefromServer(std::string str);
};

#endif