#include "../server.hpp"

void server::list(std::vector<std::string> params, std::map<int, client>::iterator client) {
    std::vector<Channels>::iterator it_channels = _Channels.begin();
    if (params.size() == 1)
    {
        client->second.ServertoClientPrefix(RPL_LISTSTART(client->second.getNickname()));
        for (; it_channels != _Channels.end(); it_channels++)
        {
            std::stringstream ss;
            ss << it_channels->getMembers().size();
            client->second.ServertoClientPrefix(RPL_LIST(client->second.getNickname(), it_channels->getName(), ss.str(), it_channels->geTopic()));
        }
        client->second.ServertoClientPrefix(RPL_LISTEND(client->second.getNickname()));
    }
    else
    {
        std::string channels;
        channels = params[1];
        size_t pos;
        size_t index = 0;
        std::string channel_name;
        client->second.ServertoClientPrefix(RPL_LISTSTART(client->second.getNickname()));
        while (1337)
        {
            pos = channels.find(',', index);
            channel_name = channels.substr(index, pos - index);
            index = pos + 1;
            Channels* ch = getChannel(channel_name);
            if (ch)
            {
                std::stringstream ss;
                ss << ch->getMembers().size();
                client->second.ServertoClientPrefix(RPL_LIST(client->second.getNickname(), ch->getName(), ss.str(), ch->geTopic()));
            }
            if (pos == std::string::npos)
                break;
        }
        client->second.ServertoClientPrefix(RPL_LISTEND(client->second.getNickname()));
    }
}