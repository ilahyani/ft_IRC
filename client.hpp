/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 08:32:30 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/13 17:56:59 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class client {
    int				_socket;
    std::string		_passwd;
    std::string		_hostname;
    std::string		_nickname;
    std::string		_username;
    std::string		_realname;
	//channels
    public:
        bool    _isOpreator;
        bool    _isGuest;
        client();
        client(int _socket);
        ~client();
};

#endif