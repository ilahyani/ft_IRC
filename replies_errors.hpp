/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies_errors.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:37:29 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/31 01:17:19 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define RPL_WELCOME(nick, network, user, host)  "001 " + nick + " :Welcome to the " + network + " Network, " + nick + "!" + user + "@" + host
#define RPL_YOURHOST(nick, server_name)         "002 " + nick + " :Your host is " + server_name
#define RPL_CREATED(nick, date)                 "003 " + nick + " :This server was created " + date
#define RPL_MOTD(nick, line)                    "372 " + nick + " :" + line
#define RPL_ENDOFMOTD(nick)                     "376 " + nick + " :End of /MOTD command"
#define ERR_NEEDMOREPARAMS(nick)                "461 " + nick + " :Not enough parameters"
#define ERR_PASSWDMISMATCH(nick)                "464 " + nick + " :Incorrect password"
#define ERR_UNKNOWNCOMMAND(nick, cmd)           "421 " + nick + " " + cmd + " :Unknown command"
#define ERR_ERRONEUSNICKNAME(nick)              "432 " + nick + " :Erroneus nickname"
#define ERR_NICKNAMEINUSE(nick)                 "433 " + nick + " :Nickname is already in use"
#define ERR_ALREADYREGISTRED(nick)              "462 " + nick + " :You may not reregister"
#define ERR_CANNOTSENDTOCHAN(nick)              "404 " + nick + " :Cannot send to channel"
#define ERR_NOTEXTTOSEND(nick)                  "412 " + nick + " :No text to send"
#define ERR_NOSUCHNICK(nick,nick_channel)       "401 " + nick + " " + nick_channel + " :No such nick/channel"
#define ERR_BADCHANNAME(nick)                   "479 " + nick + " :Invalid channel name"
#define ERR_USERONCHANNEL(nick, ch)             "443 " + nick + " " + ch + " :is already on channel"
#define RPL_NAMREPLY(nick, ch, members)         "353 " + nick + " = " + ch + " :" + members
#define RPL_ENDOFNAMES(nick, ch)                "366 " + nick + " " + ch + " :End of /NAMES list"
#define ERR_NOSUCHCHANNEL(nick, ch)             "403 " + nick + " " + ch + " :No such channel"
#define RPL_TOPIC(nick, ch, topic)              "332 " + nick + " " + ch + " :" + topic
#define ERR_NOTONCHANNEL(nick, ch)              "442 " + nick + " " + ch + " :You're not on that channel"
#define RPL_NOTOPIC(nick, ch)                   "331 " + nick + " " + ch + " :No topic is set"
#define ERR_UNKNOWNMODE(nick, char)             "472 " + nick + " " + char + " :is unknown mode char to me"
#define ERR_CHANNELISFULL(nick, ch)             "471 " + nick + " " + ch + " :Cannot join channel (+l)"
#define ERR_INVITEONLYCHAN(nick, ch)            "473 " + nick + " " + ch + " :Cannot join channel (+i)"
#define ERR_BADCHANNELKEY(nick, ch)             "475 " + nick + " " + ch + " :Cannot join channel (+k)"
#define ERR_CHANOPRIVSNEEDED(nick, ch)          "482 " + nick + " " + ch + " :You're not channel operator"
#define ERR_USERNOTINCHANNEL(nick, ch)          "441 " + nick + " " + ch + " :They aren't on that channel"
#define RPL_INVITING(rec, sen, ch)              "341 " + rec + " " + sen + " " + ch
#define ERR_NOSUCHSERVER(nick, ser)             "402 " + nick + " " + ser + " :No such server"
#define ERR_NOORIGIN(nick)                      "409 " + nick + " :No origin specified"
#define RPL_YOUREOPER(nick)                     "381 " + nick + " :You are now an IRC operator"
#define ERR_NOOPERHOST(nick)                    "491 " + nick + " :No O-lines for your host"
#define ERR_USERSDONTMATCH(nick)                "502 " + nick + " :Cant change mode for other users"
#define RPL_UMODEIS(nick, mode)                 "221 " + nick + " " + mode

#define ERR_NOTEXTTOSEND(nick)                  "412 " + nick + " :No text to send"
#define ERR_NOPRIVILEGES(nick)                  "481 " + nick + " :Permission Denied- You're not an IRC operator"

#define RPL_LISTSTART(nick)                     "321 " + nick + " Channel :Users Name"
#define RPL_LIST(nick, ch, nb, topic)           "322 " + nick + " " + ch + " " + nb + " :" + topic
#define RPL_LISTEND(nick)                       "323 " + nick + " :End of /LIST"