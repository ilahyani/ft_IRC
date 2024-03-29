#include "server.hpp"

void server::_cmdMapinit() {
    std::string cmd_strings[] = {"pass", "nick", "user", "join", "kick", "part", "notice", "privmsg", "quit"
    , "topic", "names", "list", "invite", "mode", "bot", "pong", "oper", "wallops", "whois"};
    cmd cmd_ptrs[] = {&server::pass, &server::nick,
     &server::user, &server::join, &server::kick, 
     &server::part, &server::notice, &server::privmsg, 
    &server::quit, &server::topic, &server::names, 
    &server::list, &server::invite, &server::mode, 
    &server::bot, &server::pong, &server::oper, &server::wallops, &server::whois};
    int num_cmds = sizeof(cmd_ptrs) / sizeof(cmd);

    for (int i = 0; i < num_cmds; i++)
        _cmdMap.insert(std::make_pair(cmd_strings[i], cmd_ptrs[i]));
}

server::server() {
    _cmdMapinit();
}

server::server(int port, std::string passwd) : _port(port), _passwd(passwd) {
    _cmdMapinit();
}

server::~server() {
}

std::string server::getHostAdresse(){
    std::system( "ifconfig | grep 'inet ' | awk 'NR==2 {print $2}' > .log" );
	std::stringstream ss;
	ss << std::ifstream( ".log" ).rdbuf();
	std::system( "rm -f .log" );
	return (ss.str().substr( 0, ss.str().find( '\n' ) ));
}

std::string server::getTimeCreatedServer(){
    return _timeCreated;
}

bool server::startServ() {
    int ov = 1;
    struct pollfd fd;

    _password_server = "123456";
    time_t now = time(0);
    tm *gmtm = gmtime(&now);
    _timeCreated = asctime(gmtm);
    _timeCreated.erase(std::remove(_timeCreated.begin(), _timeCreated.end(), '\n'), _timeCreated.end());
    _hostAdr = getHostAdresse();
    _listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_listenSocket < 0)
        return std::cerr << "Failed to create socket\n", false;
    if (setsockopt(_listenSocket, SOL_SOCKET, SO_REUSEADDR, &ov, sizeof(ov)) < 0
        || fcntl(_listenSocket, F_SETFL, O_NONBLOCK) < 0) {
            close (_listenSocket);
            return std::cerr << "Unexpected error\n", false;
    }
    memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(_listenSocket, (struct sockaddr *)&_addr, sizeof(_addr))) //reinterpret cast<>
        return std::cerr << "Failed to bind socket, Port already in use\n", false;

    if (listen(_listenSocket, 32) < 0) {
        close (_listenSocket);
        return std::cerr << "Failed to listen()\n", false;
    }

    fd.fd = _listenSocket;
    fd.events = POLLIN;
    _fdsVec.push_back(fd);
    std::cout << "Starting the IRC Server, and listening on port: " << _port << "\nEnjoy the trip with us !\n";
    while (true) {
        int rv = poll(&_fdsVec[0], _fdsVec.size(), -1);
        if (rv < 0)
            return std::cerr << "Poll() system call failed\n", false;
        if (_fdsVec[0].revents == POLLIN)
        {
            std::cout << "New client is connected, Welcome aboard!\n";
            addNewClient();
        }
        else
            checkConnectedClients();
    }
    return true;
}

void server::addNewClient() {
    struct pollfd fd;
    socklen_t addr_len = sizeof(_addr);

    _newSocket = accept(_listenSocket, (struct sockaddr *)&_addr, &addr_len);
    if (_newSocket < 0)
    {
        std::cerr << "Failed to accept connection\n";
        return;
    }
    std::string localhostcheck(inet_ntoa(_addr.sin_addr));
    fd.fd = _newSocket;
    fd.events = POLLIN;
    _fdsVec.push_back(fd);
    client newClient(_newSocket);

    if (localhostcheck == "127.0.0.1")
        localhostcheck = _hostAdr;
    newClient.setHostIp(localhostcheck);
    newClient.setServerIp(_hostAdr);
    newClient.setJoiningTime(std::time(NULL));
    _connectedClients.insert(std::make_pair(_newSocket, newClient));
}

void server::checkConnectedClients() {
    int recvBytes;

    for (size_t i = 1; i < _fdsVec.size(); i++) {
        if (_fdsVec.at(i).revents == POLLIN) {
            memset(_buff, 0, sizeof(_buff));
            recvBytes = recv(_fdsVec[i].fd, _buff, sizeof(_buff), 0);
            if (recvBytes == -1) {
                std::cerr << "Unexpected Error! Closing connection with "
                    << (_connectedClients.at(_fdsVec.at(i).fd).isGuest ? "guest"
                    : _connectedClients.at(_fdsVec.at(i).fd).getNickname())
                    << std::endl;
                _connectedClients.erase(_fdsVec.at(i).fd);
                close(_fdsVec.at(i).fd);
                _fdsVec.erase(_fdsVec.begin() + i);
                i--;
            }
            if (recvBytes == 0) {
                if (_connectedClients.at(_fdsVec.at(i).fd).isGuest)
                    std::cout << "Guest client left the server\n";
                else
                    std::cout << _connectedClients.at(_fdsVec.at(i).fd).getNickname() << " left the server\n";
                _connectedClients.erase(_fdsVec.at(i).fd);
                close(_fdsVec.at(i).fd);
                _fdsVec.erase(_fdsVec.begin() + i);
            }
            else
                parseDataAndRespond(i);
        }   
    }
}

void server::parseDataAndRespond(size_t pos) {
    std::vector<std::string>    cmdVec;
    std::string                 msg(_buff);
    size_t                      msgEnd;
    char                        str[512];

    std::string     str1;
    std::string     cm;

    msgEnd = msg.find_first_of("\r\n");
    if (msgEnd == std::string::npos)
        _connectedClients.at(_fdsVec.at(pos).fd).clientBuff += msg;
    else {
        _connectedClients.at(_fdsVec.at(pos).fd).clientBuff += msg.substr(0, msgEnd);
        std::strcpy(str, _connectedClients.at(_fdsVec.at(pos).fd).clientBuff.c_str());

        str1 = _connectedClients.at(_fdsVec.at(pos).fd).clientBuff;

        int i = 0;
        int j = 0;
        while (i < (int)str1.size())
        {
            if (str1[i] == ' ')
                i++;
            if (str1[i] == ':')
            {
                j = 0;
                i++;
                while (str1[i] && j < (int)str1.size())
                    str[j++] = str1[i++];
                str[j] = '\0';
                cmdVec.push_back(str);
                break;
            }
            j = 0;
            while (str1[i] && (str1[i] != ' '))
                str[j++] = str1[i++];
            str[j] = '\0';
            cmdVec.push_back(str);
            i++;
        }
        if (!cmdVec.empty())
            std::transform(cmdVec[0].begin(), cmdVec[0].end(), cmdVec[0].begin(), ::tolower);
        _connectedClients.at(_fdsVec.at(pos).fd).clientBuff.clear();
        respondToClient(cmdVec, _connectedClients.find(_fdsVec.at(pos).fd));
    }
}

void server::respondToClient(std::vector<std::string> cmdVec, std::map<int, client>::iterator client) {
    std::map<std::string, cmd>::iterator cmd_it;
    std::string command;

    if (cmdVec.size() > 0)
        command = cmdVec[0];
    cmd_it = _cmdMap.find(command);
    if (client->second.loggedIn) {
        if (!client->second.isGuest) {
            if (cmd_it != _cmdMap.end())
                (this->*(cmd_it->second))(cmdVec, client);
            else
                client->second.ServertoClientPrefix(ERR_UNKNOWNCOMMAND(client->second.getNickname(), command));
        }
        else {
            if (cmd_it != _cmdMap.end() && (!cmd_it->first.compare("nick") || !cmd_it->first.compare("user"))) 
            {
                if(!cmd_it->first.compare("nick"))
                    server::nick(cmdVec, client);
                else if (!cmd_it->first.compare("user"))
                    server::user(cmdVec, client);
            }
        }
    }
    else {
        if (cmd_it != _cmdMap.end() && !cmd_it->first.compare("pass"))
            server::pass(cmdVec, client);
    }
}

std::string server::getPasswd(){
    return _passwd;
}

std::vector<Channels>& server::getChannels(){
    return _Channels;
}

bool server::Check_client(int socket)
{   
    std::map<int, client>::iterator it = _connectedClients.begin();
    for (; it != _connectedClients.end(); it++)
    {
        if (socket == it->second.getsocket())
            return true;
    }
    return false;
}

client* server::get_client(std::string nick)
{   
    std::map<int, client>::iterator it = _connectedClients.begin();
    for (; it != _connectedClients.end(); it++)
    {
        if (nick == it->second.getNickname())
            return &it->second;
    }
    return NULL;
}

Channels* server::getChannel(std::string channel_name)
{
    std::vector<Channels>::iterator it = _Channels.begin();
    for (; it != _Channels.end(); it++)
    {
        if (channel_name == it->getName())
            return &(*it);
    }
    return NULL;
}

void server::sendToClientById(int receiver, client sender, std::string message)
{
    std::string msg = ":" + sender.getPrefixClient() + message + "\r\n";
    if(Check_client(receiver))
        send(receiver, msg.c_str(), msg.length(), 0);
    msg.clear();
}

std::pair<client, ROLE>* server::checkUserIsInChannel(client c, Channels *ch)
{
    std::vector<std::pair<client, ROLE> > Members = ch->getMembers();
    std::vector<std::pair<client, ROLE> >::iterator it = Members.begin();

    while (it != Members.end())
    {
        if (it->first.getsocket() == c.getsocket())
            return &*it;
        it++;
    }
    return NULL;
}

void server::send_msg_to_clients_who_in_channel(Channels *ch, client c, std::string cmd)
{
    int i = 0;
    std::vector<std::pair<client, ROLE> > clients = ch->getMembers();
    std::string message = ":" + c.getPrefixClient() + cmd + "\r\n";
    while (i < (int)clients.size())
    {
        if (c.getsocket() != clients[i].first.getsocket())
            send(clients[i].first.getsocket(), message.c_str(), message.length(), 0);
        i++;
    }
}

void server::send_to_all_in_channel(Channels *ch, client c, std::string cmd)
{
    int i = 0;
    std::vector<std::pair<client, ROLE> > clients = ch->getMembers();
    std::string message = ":" + c.getPrefixClient() + cmd + "\r\n";
    while (i < (int)clients.size())
    {
        send(clients[i].first.getsocket(), message.c_str(), message.length(), 0);
        i++;
    }
}

void server::deleteClient(client &c)
{
    std::vector<struct pollfd>::iterator it = _fdsVec.begin();
    while (it != _fdsVec.end())
    {
        if (c.getsocket() == it->fd)
        {
            _fdsVec.erase(it);
            close(c.getsocket());
            return ;
        }
        it++;
    }
}

ROLE server::checkRoleUserInChannel(client& c, Channels *ch)
{
    std::vector<std::pair<client, ROLE> > Members = ch->getMembers();
    std::vector<std::pair<client, ROLE> >::iterator it = Members.begin();

    while (it != Members.end())
    {
        if (it->first.getsocket() == c.getsocket() && it->second == OPERATOR)
            return OPERATOR;
        it++;
    }
    return MEMBER;
}

std::string server::getClientsChannel(Channels *ch)
{
    std::string str;
    std::vector<std::pair<client, ROLE> > clients = ch->getMembers();

    int i = clients.size() - 1;
    while (i >= 0)
    {
        if (clients[i].second == OPERATOR)
            str += ("@" + clients[i].first.getNickname() + " ");
        else
            str += (clients[i].first.getNickname() + " ");
        i--;
    }
    return str;
}
