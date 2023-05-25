#include "../server.hpp"

void server::names(std::vector<std::string> params, std::map<int, client>::iterator client) {
    (void)params;(void)client;
    std::cout << "NAMES command called\n";

    int k = 0;
    if (params.size() == 1)
    {
        if (_Channels.size() != 0)
        {
            if (k == 1)
            {
                return;
            }
            else
            {
                for (size_t i = 0; i < _Channels.size(); i++)
                {
                    for (size_t j = 0; j < _Channels[i].getMembers().size(); j++)
                    {
                        std::string client_Nick = _Channels[i].getMembers().at(j).first.getNickname();
                        std::string Channel_name = _Channels[i].getName();
                        std::string str = "Channel " + Channel_name + " : " + client_Nick;
                        client->second.response(str);
                    }
                }
            }
        }
        else
        {
            std::cout << "not channel in server" << std::endl;
        }
    }
    if (params.size() == 2)
    {
        if (check_multichannel(params[1]))
            {
                std::vector<std::string> Channels_list = ft_split_channels(params[1]);
                for (size_t i = 0; i < Channels_list.size(); i++)
                {
                    int channelExist = findChannelByName(Channels_list[i], client->second);
                    if (channelExist == 1)
                    {
                        Channels *ch = getChannel(Channels_list[i]);
                        if (k == 1)
                        {
                            return ;
                        }
                        else
                        {
                            for (size_t j = 0; j < ch->getMembers().size(); j++)
                            {
                                std::string client_Nick = ch->getMembers().at(j).first.getNickname();
                                std::string Channel_name = ch->getName();
                                std::string str = "Channel " + Channel_name + " : " + client_Nick;
                                client->second.response(str);
                            }
                        }
                    }
                }
            }
            else
            {
                int channelExist = findChannelByName(params[1], client->second);
                if (channelExist == 1)
                {
                    Channels *ch = getChannel(params[1]);
                    if (k == 1)
                    {
                        return ;
                    }
                    else
                    {
                        for (size_t j = 0; j < ch->getMembers().size(); j++)
                        {
                            std::string client_Nick = ch->getMembers().at(j).first.getNickname();
                            std::string Channel_name = ch->getName();
                            std::string str = "Channel " + Channel_name + " : " + client_Nick;
                            client->second.response(str);
                        }
                    }
                }
            }
    }
    else 
    {

    }
    client->second.response(": End of /NAMES list");
}