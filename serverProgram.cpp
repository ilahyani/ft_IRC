/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverProgram.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:48:17 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/13 08:56:44 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#define SERVER_PORT  12345

int main (int argc, char *argv[])
{
    int    on = 1, nfds = 1, current_size = 0, i, j, len, rc;
    int    listen_sd = -1, new_sd = -1;
    int    desc_ready, end_server = false, compress_array = false;
    int    close_conn;
    int    timeout;
    char   buffer[1024];
    struct pollfd fds[200];
    struct sockaddr_in   addr;

    if ((listen_sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("socket() failed");
        exit(-1);
    }
    if ((rc = setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on))) < 0)
    {
        perror("setsockopt() failed");
        close(listen_sd);
        exit(-1);
    }
    rc = fcntl(listen_sd, F_SETFL, O_NONBLOCK);
    if (rc < 0)
    {
        perror("fcntl() failed");
        close(listen_sd);
        exit(-1);
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    memcpy(&addr.sin_addr, &in6addr_any, sizeof(in6addr_any));
    addr.sin_port        = htons(SERVER_PORT);
    rc = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr));
    if (rc < 0)
    {
        perror("bind() failed");
        close(listen_sd);
        exit(-1);
    }
    rc = listen(listen_sd, 32);
    if (rc < 0)
    {
        perror("listen() failed");
        close(listen_sd);
        exit(-1);
    }
    memset(fds, 0 , sizeof(fds));
    fds[0].fd = listen_sd;
    fds[0].events = POLLIN;
    timeout = (3 * 60 * 1000);
    while (end_server == false)
    {
        std::cout << "Waiting on poll()...\n";
        rc = poll(fds, nfds, timeout);
        if (rc < 0)
        {
            perror(" poll() failed");
            break;
        }
        if (rc == 0)
        {
            std::cout << " poll() timed out.  End program.\n";
            break;
        }
        current_size = nfds;
        for (i = 0; i < current_size; i++)
        {
            if(fds[i].revents == 0)
                continue;
            if(fds[i].revents != POLLIN)
            {
                std::cout << "  Error! revents = " << fds[i].revents << "\n";
                end_server = true;
                break;

            }
            if (fds[i].fd == listen_sd)
            {
                std::cout << " Listening socket is readable\n";
                do
                {
                    new_sd = accept(listen_sd, NULL, NULL);
                    if (new_sd < 0)
                    {
                        if (errno != EWOULDBLOCK)
                        {
                            perror(" accept() failed");
                            end_server = true;
                        }
                        break;
                    }
                    std::cout << " New incoming connection - " << new_sd << "\n";
                    fds[nfds].fd = new_sd;
                    fds[nfds].events = POLLIN;
                    nfds++;
                }
                while (new_sd != -1);
            }
            else
            {
                std::cout  << fds[i].fd << " Descriptor is readable\n";
                close_conn = false;
                do
                {
                    rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                    if (rc < 0)
                    {
                        if (errno != EWOULDBLOCK)
                        {
                            perror(" recv() failed");
                            close_conn = true;
                        }
                        break;
                    }
                    if (rc == 0)
                    {
                        std::cout << " Connection closed\n";
                        close_conn = true;
                        break;
                    }
                    len = rc;
                    std::cout << len << " bytes received\n";
                    rc = send(fds[i].fd, buffer, len, 0);
                    if (rc < 0)
                    {
                        perror(" send() failed");
                        close_conn = true;
                        break;
                    }
                    std::cout << "buffer: " << buffer << "\n";
                }
                while(true);
                if (close_conn)
                {
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    compress_array = true;
                }
            }
        }
        if (compress_array)
        {
            compress_array = false;
            for (i = 0; i < nfds; i++)
            {
                if (fds[i].fd == -1)
                {
                    for(j = i; j < nfds; j++)
                        fds[j].fd = fds[j+1].fd;
                    i--;
                    nfds--;
                }
            }
        }
    }
    for (i = 0; i < nfds; i++)
        if(fds[i].fd >= 0)
            close(fds[i].fd);
    return 0;
}

// int main(void) {
//     int s, new_s, n;
//     struct sockaddr_in address;
//     socklen_t addr_size = sizeof(address);
//     const int PORT = 8080;
//     const int BACKLOG = 10;
//     const int BUF_SIZE = 1024;
//     char buf[BUF_SIZE];
//     struct pollfd fds[BACKLOG];
//     char *resp = "Hell world!";

//     if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
//         return (perror(NULL), 1);
//     memset((char *)&address, 0, sizeof(address));
//     address.sin_family = AF_INET;
//     address.sin_port = htons(PORT);
//     address.sin_addr.s_addr = htonl(INADDR_ANY);
//     if (bind (s, (struct sockaddr *)&address, addr_size) == -1)
//         return (perror(NULL), 1);
//     if (listen(s, BACKLOG) == -1)
//         return (perror(NULL), 1);
//     while (true) {
//         std::cout << "\n------------ Waiting for a new connection ------------\n";
//         if ((new_s = accept(s, NULL, NULL)) == -1)
//             return (perror(NULL), 1);
//         std::cout << "connection accepted!\n";
//         memset(buf, 0, BUF_SIZE);
//         n = read(new_s, buf, BUF_SIZE);
//         if (n < 0)
//             return (std::cerr << "Error reading from socket\n", 1);
//         std::cout << "Client msg:\n" << buf << std::endl;
//         n = write (new_s, resp, strlen(resp));
//         if (n < 0)
//             return (std::cerr << "Error writing to socket\n", 1);
//     }
//     close(new_s);
//     close(s);
//     return 0;
// }

