#include "../server.hpp"

void server::list(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void) client;
    // std::vector<Channels>::iterator it_channels = _Channels.begin();
    // if (params.size() == 1)
    // {
    //     client->second.responsefromServer(RPL_LISTSTART(client->second.getNickname()));
    //     for (; it_channels != _Channels.end(); it_channels++)
    //     {
    //         std::stringstream ss;
    //         ss << it_channels->getMembers().size();
    //         client->second.responsefromServer(RPL_LIST(client->second.getNickname(), it_channels->getName(), ss.str(), it_channels->geTopic()));
    //     }
    //     client->second.responsefromServer(RPL_LISTEND(client->second.getNickname()));
    // }
    // else
    // {
        std::string channels;

        channels = params[1];

        int i = 0;
        size_t pos = channels.find(',');
        while ((pos = channels.find(',')) != std::string::npos)
        {
            std::cout << channels.substr(i, pos) << "\n";
            i = pos;
        }
    // }
}