#include "../server.hpp"
#include "../client.hpp"

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

    if (params.size() == 1)
    {
        if (_Channels.size() != 0)
        {
            for (int i = 0; i < (int)_Channels.size(); i++)
            {
                // if (bool +k)
                // {
                    // std::string Channel_name = _Channels[i].getName();
                    // std::cout << _Channels[i].getName() << std::endl;
                    // std::string str = "Channel " + Channel_name + " : Privete";
                    // client->second.response(str);
                // }
                // else
                // {
                    std::string Channel_name = _Channels[i].getName();
                    size_t ChannelMembers = _Channels[i].getMembers().size();
                    std::cout << "ChannelMembers ==> "<< ChannelMembers << std::endl;
                    std::string str = "Channel " + Channel_name + " : " + _Channels[i].geTopic();
                    client->second.response(str);
                // }

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
                for (int i = 0; i < (int)Channels_list.size(); i++)
                {
                    if ()
                    {
                         // std::string Channel_name = _Channels[i].getName();
                        // std::cout << _Channels[i].getName() << std::endl;
                        // std::string str = "Channel " + Channel_name + " : Privete";
                        // client->second.response(str);
                    }
                    else
                    {

                    }
                }
            }
            else
            {
                int channelExist = findChannelByName(params[1], client->second);
                if (channelExist == 1)
                {
                    Channels *ch = getChannel(params[1]);
                    client->second.response("khobza zwina");
                    std::cout << "Channel: " << ch->getName() << std::endl;
                    
                }
            }
        
    }
}