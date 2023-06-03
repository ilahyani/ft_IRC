#include "client.hpp"

client::client() {
    isGuest = true;
    isOpreator = false;
    loggedIn = false;
    isRegistered = false;
    wallops = true;
    isInvisible = false;
}

client:: client(int socket) : _socket(socket) {
    isGuest = true;
    isOpreator = false;
    loggedIn = false;
    isRegistered = false;
    wallops = true;
    isInvisible = false;
}

client::~client() {}

const int& client::getsocket() {
    return _socket;
}

const std::string& client::getNickname() {
    return _nickname;
}

const std::string& client::getRealname() {
    return _realname;
}

const std::string& client::getUsername() {
    return _username;
}

const std::string& client::getServerIp() {
    return _serverip;
}

const std::string& client::getHostIp(){
    return _hostip;
}

void client::setHostIp(std::string hostip){
    _hostip = hostip;
}

const std::string& client::getPasswd() {
    return _passwd;
}

const std::string client::getJoiningTime(){
    std::stringstream ss;
    ss << _time;
    return ss.str();
}

void client::setJoiningTime(std::time_t t){
    _time = t;
}

void client::setNickname(std::string nickname) {
    _nickname = nickname;
}

void client::setServerIp(std::string serverip) {
   _serverip = serverip;
}

std::string client::getPrefixClient() {
    return getNickname() + "!" + getUsername() + "@" + getHostIp() + " ";
}

void client::ClienttoClientPrefix(std::string str) {
    print(":" + getPrefixClient() + str);
}

void client::ServertoClientPrefix(std::string str) {
    print(":" + getServerIp() + " " + str);
}

void client::print(std::string str) {
    std::string buff = str + "\r\n";
    if (send(_socket, buff.c_str(), buff.length(), 0) < 0)
        throw std::runtime_error("An error occurred while attempting to send a message to the client.\n");
}

void client::welcome(std::string dateCreated) {
    if (isGuest && !getNickname().empty() && !getRealname().empty() && !getUsername().empty())
    {
        std::cout << getNickname() << " is logged in\n";
        isGuest = false;
        isRegistered = true;
        ServertoClientPrefix(RPL_WELCOME(getNickname(), "IRC", getUsername(), getHostIp()));   
        ServertoClientPrefix(RPL_YOURHOST(getNickname(), getHostIp()));
        ServertoClientPrefix(RPL_CREATED(getNickname(), dateCreated)); 
        ServertoClientPrefix(RPL_MOTD(getNickname(), "- " + getServerIp() + " Message of the day"));
        ServertoClientPrefix(RPL_MOTD(getNickname(), " ___________  _____  _____ ___________ _   _ "));
        ServertoClientPrefix(RPL_MOTD(getNickname(), "|_   _| ___ \\/  __ \\/  ___|  ___| ___ \\ | | |"));
        ServertoClientPrefix(RPL_MOTD(getNickname(), "  | | | |_/ /| /  \\/\\ `--.| |__ | |_/ / | | |"));
        ServertoClientPrefix(RPL_MOTD(getNickname(), "  | | |    / | |     `--. \\  __||    /| | | |"));
        ServertoClientPrefix(RPL_MOTD(getNickname(), " _| |_| |\\ \\ | \\__/\\/\\__/ / |___| |\\ \\\\ \\_/ /"));
        ServertoClientPrefix(RPL_MOTD(getNickname(), " \\___/\\_| \\_| \\____/\\____/\\____/\\_| \\_|\\___/ "));
        ServertoClientPrefix(RPL_MOTD(getNickname(), " "));
        ServertoClientPrefix(RPL_ENDOFMOTD(getNickname()));
        ServertoClientPrefix(RPL_UMODEIS(getNickname(), "+w"));
    }
}

void client::setRealname(std::string realname) { _realname = realname; }
void client::setUsername(std::string username) { _username = username; }
