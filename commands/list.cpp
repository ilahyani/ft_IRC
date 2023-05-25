#include "../server.hpp"

bool check_multichannel(const std::string& str)
{
    return str.find(',') != std::string::npos;
}


std::vector<std::string> ft_split_channels(std::string channels)
{
    std::vector<std::string> channelList;

    std::istringstream iss(channels);
    std::string channel;
    
    while (std::getline(iss, channel, ','))
    {
        channelList.push_back(channel);
    }
    return (channelList);
}

void server::list(std::vector<std::string> params, std::map<int, client>::iterator client)
{
    (void)params;(void)client;
    std::cout << "LIST command called\n";


    int k = 0;
    if (params.size() == 1)
    {
        if (_Channels.size() != 0)
        {
            for (int i = 0; i < (int)_Channels.size(); i++)
            {
                if (k == 1)
                {
                    std::string Channel_name = _Channels[i].getName();
                    std::string str = "Channel " + Channel_name + " : Private";
                    client->second.response(str);
                }
                else
                {
                    std::string Channel_name = _Channels[i].getName();
                    std::string str = "Channel " + Channel_name + " : " + _Channels[i].geTopic();
                    client->second.response(str);
                }

            }
        }
        else
        {
            std::cout << "not channel in server" << std::endl;
        }
    }
    else if (params.size() == 2)
    {

            if (check_multichannel(params[1]))
            {
                std::vector<std::string> Channels_list = ft_split_channels(params[1]);
                for (size_t i = 0; i < Channels_list.size(); i++)
                {
                    int channelExist = findChannelByName(Channels_list[i], client->second);
                    if (channelExist == 1)
                    {
                        if (k == 1)
                        {
                            std::string Channel_name = _Channels[i].getName();
                            std::string str = "Channel " + Channel_name + " : Private";
                            client->second.response(str);
                        }
                        else
                        {
                            std::string Channel_name = _Channels[i].getName();
                            std::string str = "Channel " + Channel_name + " : " + _Channels[i].geTopic();
                            client->second.response(str);
                        }
                    }
                    else
                    {
                        std::cout << "channel not in server" << "\n";  
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
                        std::string Channel_name = ch->getName();
                        std::string str = "Channel " + Channel_name + " : Private";
                        client->second.response(str);
                    }
                    else
                    {
                        std::string Channel_name = ch->getName();
                        std::string str = "Channel " + Channel_name + " : " + ch->geTopic();
                        client->second.response(str);
                    }
                    
                }
                else
                {
                    std::cout << "channel not in server" << "\n";
                }
            }
        
    }
    else
    {
        
    }
    client->second.response(": End of /LIST");
       
}