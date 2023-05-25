#include "../server.hpp"

void server::quit(std::vector<std::string> params, std::map<int, client>::iterator c)
{
    std::cout << "QUIT command called\n";

    if (params.size() < 2)
    {
        int clientExist = findClientByName(c->second.getNickname(), c->second);
        int fd_client = c->second.getsocket();
        std::map<int, client>::iterator	itClient = _connectedClients.find(fd_client);
        if (clientExist == 1)
        {
            for(size_t i = 0; i < _Channels.size(); i++)
            {
                Channels *ch = getChannel(_Channels[i].getName());
                if (checkUserIsInChannel1(c->second, ch))
                {
                    std::vector<std::pair<client, ROLE> >::iterator channelMember = ch->getMembers().end();
                    for (std::vector<std::pair<client, ROLE> >::iterator it = ch->getMembers().begin(); it != ch->getMembers().end(); ++it)
                    {
                        if (it->first.getsocket() == c->second.getsocket())
                        {
                            channelMember = it;
                            break;
                        }
                    }
                      ch->getMembers().erase(channelMember);
                }
            }
            if (itClient != _connectedClients.end())
            {
               _connectedClients.erase(itClient); 
            }
            
            std::cout << "CLIENT DISCONNECTED \n";
            close(fd_client);

        }
        else
        {
            
        }
    }
    else
    {
        std::cout << "enough params \n";
    }

    // if (params.size() <= 3)
    // {
    //     if (check_multichannel(params[1]))
    //     {
    //         std::vector<std::string> Channels_list = ft_split_channels(params[1]);
    //         for (size_t i = 0; i < Channels_list.size(); i++)
    //         {
    //             int channelExist = findChannelByName(Channels_list[i], c->second);
    //             if (channelExist == 1)
    //             {
    //                 Channels *ch = getChannel(Channels_list[i]);
    //                 if (checkUserIsInChannel1(c->second, ch))
    //                 {
    //                     std::vector<std::pair<client, ROLE> >::iterator channelMember = ch->getMembers().end();
    //                     for (std::vector<std::pair<client, ROLE> >::iterator it = ch->getMembers().begin(); it != ch->getMembers().end(); ++it) {
    //                         if (it->first.getsocket() == c->second.getsocket())
    //                         {
    //                             channelMember = it;
    //                             break;
    //                         }
    //                     }
    //                     ch->getMembers().erase(channelMember);
    //                     std::cout << "user leave "  + params[1] + "\n"; 
    //                 }
    //                 else
    //                 {
    //                     c->second.response(ERR_NOTONCHANNEL(c->second.getNickname(), params[1]));
    //                 }
    //             }
    //         }
    //     }
    //     else
    //     {
    //         int channelExist = findChannelByName(params[1], c->second);
    //         if (channelExist == 1)
    //         {
    //             Channels *ch = getChannel(params[1]);
    //             if (checkUserIsInChannel1(c->second, ch))
    //             {
    //                 std::vector<std::pair<client, ROLE> >::iterator channelMember = ch->getMembers().end();
    //                 for (std::vector<std::pair<client, ROLE> >::iterator it = ch->getMembers().begin(); it != ch->getMembers().end(); ++it) {
    //                     if (it->first.getsocket() == c->second.getsocket())
    //                     {
    //                         channelMember = it;
    //                         break;
    //                     }
    //                 }
    //                 ch->getMembers().erase(channelMember);
    //                 std::cout << "user leave "  + params[1] + "\n"; 
    //             }
    //             else
    //             {
    //                 c->second.response(ERR_NOTONCHANNEL(c->second.getNickname(), params[1]));
    //             }
    //         }
            
    //     }
    // }
    // else
    // {
    //     std::cout << "enough params \n";
    // }
}