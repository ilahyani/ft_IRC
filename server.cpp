/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:10:31 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/16 00:22:24 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

// This function initializes the command map by creating a mapping between each command and its corresponding function pointer
void server::_cmdMapinit() {
    // An array of command strings
    std::string cmd_strings[] = {"pass", "nick", "user", "join", "kick", "part", "notice", "privmsg", "quit", "topic"};
    // An array of command function pointers
    cmd cmd_ptrs[] = {&server::pass, &server::nick, &server::user, &server::join, &server::kick, &server::part, &server::notice, &server::privmsg, &server::quit, &server::topic};
    // The total number of commands
    int num_cmds = sizeof(cmd_ptrs) / sizeof(cmd);

    // Create a mapping between each command string and its corresponding function pointer, and insert the pair into the command map
    for (int i = 0; i < num_cmds; i++)
        _cmdMap.insert(std::make_pair(cmd_strings[i], cmd_ptrs[i]));
}

// This is the default constructor for the server class
server::server() {
    // Call the command map initialization function
    _cmdMapinit();
}

// This is a constructor for the server class that takes in a port number and password
server::server(int port, std::string passwd) : _port(port), _passwd(passwd) {
    // Call the command map initialization function
    _cmdMapinit();
}

// This is the destructor for the server class
server::~server() {
    // for (size_t i = _fdsVec.size(); i >= 0; i--)
    //     close(_fdsVec[i].fd);
}

// This function starts the server and listens for incoming client connections
bool server::startServ() {
    // Variable to enable reuse of the socket address
    int ov = 1;
    // Poll file descriptor struct
    struct pollfd fd;

    // Create a TCP socket for the server to listen on
    _listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_listenSocket < 0)
        return std::cerr << "Failed to create socket\n", false;

    // Set the socket options for reuse of the socket address and non-blocking mode
    if (setsockopt(_listenSocket, SOL_SOCKET, SO_REUSEADDR, &ov, sizeof(ov)) < 0
        || fcntl(_listenSocket, F_SETFL, O_NONBLOCK) < 0) {
            close (_listenSocket);
            return std::cerr << "Unexpected error\n", false;
    }

    // Initialize the server address and bind the socket to the specified port
    std::vector<int> second (4,100);
    memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(_listenSocket, (struct sockaddr *)&_addr, sizeof(_addr)))
        return std::cerr << "Failed to bind socket, Port already in use\n", false;

    // Listen for incoming connections on the socket
    if (listen(_listenSocket, 10) < 0) {
        close (_listenSocket);
        return std::cerr << "Failed to listen()\n", false;
    }

    // Add the listen socket to the poll file descriptor vector
    fd.fd = _listenSocket;
    fd.events = POLLIN;
    _fdsVec.push_back(fd);

    // Output welcome message to console
    std::cout << "Welcome to IRC Server\n";

    // Continuously poll for incoming data on the sockets
    while (true) {
        // Poll the file descriptor vector for events
        int rv = poll(&_fdsVec[0], _fdsVec.size(), -1);

        // Output the number of connected clients to console
        std::cout << _fdsVec.size() - 1 << " connected clients\n";

        // Handle errors that occur during polling
        if (rv < 0)
            return std::cerr << "Poll() system call failed\n", false;

        // If the listen socket has an event, add a new client to the server
        if (_fdsVec[0].revents == POLLIN)
            addNewClient();
        // Otherwise, check for events on the connected clients
        else
            checkConnectedClients();
    }
    return true;
}

// This function adds a new client to the server
void server::addNewClient() {
    // Initialize a new poll file descriptor struct
    struct pollfd fd;

    // Determine the length of the address of the accepted connection
    socklen_t addr_len = sizeof(_addr);

    // Accept a new connection and store the new socket descriptor in _newSocket
    _newSocket = accept(_listenSocket, (struct sockaddr *)&_addr, &addr_len);

    // Check if the socket descriptor is valid
    if (_newSocket < 0) {
        std::cerr << "Failed to accept connection\n";
        return;
    }

    // Print a message indicating that the connection was accepted
    std::cout << "Connection Accepted\n";

    // Set the file descriptor and event types for the new client
    fd.fd = _newSocket;
    fd.events = POLLIN;

    // Add the new file descriptor to the poll vector
    _fdsVec.push_back(fd);

    // Create a new instance of the client class and add it to the map of connected clients
    client newClient(_newSocket);
    _connectedClients.insert(std::make_pair(_newSocket, newClient));
}


void    server::checkConnectedClients() {
    int recvBytes;
    std::vector<std::string> cmd;

    // iterate over all connected clients except the listening socket
    for (size_t i = 1; i < _fdsVec.size(); i++) {

        // clear the buffer before receiving new data
        memset(_buff, 0, sizeof(_buff));
        
        // receive data from client
        recvBytes = recv(_fdsVec[i].fd, _buff, sizeof(_buff), 0);
        
        // check for errors
        if (recvBytes == -1) {
            // handle unexpected error by closing the connection with the client
            std::cerr << "Unexpected Error! Closing connection with "
                << (_connectedClients.at(_fdsVec.at(i).fd)._isGuest ? "guest"
                : _connectedClients.at(_fdsVec.at(i).fd).getHostname())
                << std::endl;
            _connectedClients.erase(_fdsVec.at(i).fd);
            close(_fdsVec.at(i).fd);
            _fdsVec.erase(_fdsVec.begin() + i);
            i--;
        }

        // check if client has disconnected
        if (recvBytes == 0) {
            if (_connectedClients.at(_fdsVec.at(i).fd)._isGuest)
                std::cout << "Guest client left the server\n";
            else
                std::cout << _connectedClients.at(_fdsVec.at(i).fd).getNickname() << " left the server\n";
            _connectedClients.erase(_fdsVec.at(i).fd);
            close(_fdsVec.at(i).fd);
            _fdsVec.erase(_fdsVec.begin() + i);
        }
        
        // if data is received, parse it
        else
            parseReceivedData(i);
    }
}
   
void server::parseReceivedData(size_t pos) {
    std::vector<std::string>    cmdVec; // vector to hold parsed command
    std::string                 msg(_buff); // received data from client
    size_t                      msgEnd; // index of end of message
    char                        *token; // string tokenizer
    char                        str[512]; // buffer to hold received data

    // find the end of the message
    msgEnd = msg.find_first_of("\r\n");
    
    // if the end of the message is not found, append the data to the client buffer
    if (msgEnd == std::string::npos)
        _connectedClients.at(_fdsVec.at(pos).fd)._clientBuff += msg;
    
    // if the end of the message is found, process the command
    else {
        // append the data to the client buffer and copy it to a temporary buffer
        _connectedClients.at(_fdsVec.at(pos).fd)._clientBuff += msg.substr(0, msgEnd);
        // _connectedClients.at(_fdsVec.at(pos).fd)._clientBuff += "    ";
        std::strcpy(str, _connectedClients.at(_fdsVec.at(pos).fd)._clientBuff.c_str());
        
        // tokenize the command and add the tokens to the vector
        token = std::strtok(str, " ");
        while (token != NULL) {
            cmdVec.push_back(token);
            token = std::strtok(NULL, " ");
        }
        
        // clear the client buffer and print the parsed command
        _connectedClients.at(_fdsVec.at(pos).fd)._clientBuff.clear();
        std::cout << "cmdVec: ";
        for (size_t i = 0; i < cmdVec.size(); i++)
            std::cout << cmdVec[i] << " ";
        std::cout << "\n";
        
        // check for errors in the command and respond accordingly
        if (!HasError(cmdVec))
            respondToClient(cmdVec, _connectedClients.find(_fdsVec.at(pos).fd));
    }
}

bool    server::HasError(std::vector<std::string> cmdVec) {
    // https://www.rfc-editor.org/rfc/rfc2812#section-2
    (void)cmdVec;
    return false;
}

void server::respondToClient(std::vector<std::string> cmdVec, std::map<int, client>::iterator client) {
    std::map<std::string, cmd>::iterator cmd_it;
    std::string command;

    // skip the prefix and find the command in the command map
    command = (cmdVec[0][0] == ':' ? cmdVec[1] : cmdVec[0]);
    cmd_it = _cmdMap.find(command);

    // if client is logged in
    if (client->second._loggedIn) {
        // if client is not a guest, execute the command if it exists
        if (!client->second._isGuest) {
            if (cmd_it != _cmdMap.end())
                (this->*(cmd_it->second))(cmdVec, client);
            else
                std::cerr << "Error: unknown command\n";
        }
        // if client is a guest, execute commands only if they are 'nick' or 'user'
        else {
            if (!cmd_it->first.compare("nick"))
                server::nick(cmdVec, client);
            else if (!cmd_it->first.compare("user"))
                server::user(cmdVec, client);
            else
                std::cout << "Please register\n";
        }
    }
    // if client is not logged in, execute 'pass' command to log in
    else {
        if (!cmd_it->first.compare("pass")) {
            server::pass(cmdVec, client);
        }
        else
            std::cout << "Please Login to the server\n";
    }
}
