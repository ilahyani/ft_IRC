/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 08:32:30 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/29 13:34:51 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "irc.hpp"

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
};

#endif