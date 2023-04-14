/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:51:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/13 18:19:54 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "client.hpp"

class server {
    int                         _listenSocket;
    int                         _newSocket;
    int                         _port;
    std::string                 _passwd;
    char                        *_buff[1024];
    struct sockaddr_in          _addr;
    std::vector<struct pollfd>  _fdsVec;
    std::map<int, client>       _connectedClients;
    public:
        server();
        ~server();
        std::string getPasswd();
        void setPasswd();
        void setPort();
        int getPort();
        bool startServ();
        void checkData();
        void parseBuff();
};

#endif