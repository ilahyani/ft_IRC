#include "../server.hpp"

bool isUsernameValid(std::string nick) {

    std::string invalidChars = " ,:;-?!&%\\/()[]{}\"'~^$#*";

    if (nick[0] == '.')
        return false;
    for (int i = 0; i < (int)nick.length(); i++)
    {
        if (invalidChars.find(nick[i]) != std::string::npos)
            return false;
    }
    return true;
}

bool isRealnameValid(std::string nick) {

    std::string invalidChars = ",:;_?!&%\\/()[]{}\"'~^$#*";

    if (nick[0] == '.')
        return false;
    for (int i = 0; i < (int)nick.length(); i++)
    {
        if (invalidChars.find(nick[i]) != std::string::npos)
            return false;
    }
    return true;
}

void server::user(std::vector<std::string> params, std::map<int, client>::iterator client) {
    
    if (params.size() < 5)
    {
        client->second.ServertoClientPrefix(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }
    
    if (client->second.isRegistered)
    {
        client->second.ServertoClientPrefix(ERR_ALREADYREGISTRED(client->second.getNickname()));
        return ;
    }

    if (params[2] == "2")
        client->second.isInvisible = true;
    else if (params[2] == "4")
        client->second.wallops = true;
    
    client->second.setUsername(params[1]);
    client->second.setRealname(params[4]);

    client->second.welcome(getTimeCreatedServer());
}