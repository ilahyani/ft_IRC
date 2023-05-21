#include "../server.hpp"


int   server::findChannelByName(std::string channel_name, client client)
{
    std::vector<Channels>::iterator it = _Channels.begin();
    for (; it != _Channels.end(); it++)
    {
        if (channel_name == it->getName())
            return (1);
    }
    client.response(ERR_NOSUCHCHANNEL(client.getNickname(), channel_name));
    return -1;
}

int   server::findClientByName(std::string nick, client client)
{
    std::map<int, client>::iterator it = _connectedClients.begin();
    for (; it != _connectedClients.end(); it++)
    {
        if (nick == it->second.getNickname())
            return 1;
    }
    return -1;
}

void server::invite(std::vector<std::string> params, std::map<int, client>::iterator client)
{
    (void)params;(void)client;
    std::cout << "INVITE command called\n";
    std::string nick = params[1];

    int channelExist = findChannelByName(params[2], client->second);
    int clientExist = findClientByName(params[1], client->second);
    // std::cout << "channel check ==" << ch->getName() << "\n";
    // if (ch != NULL)
    // if (ch != NULL || params[2] == ch->getName())
    std::cout << "channel exist=====" << channelExist << std::endl;
    if (channelExist == 1)
    {
        Channels *ch = getChannel(params[2]);
        std::cout << "channel found\n"; 
        // if (client->second.getNickname() == ch->getOwnerNickname())
        // {
            // if (get_client(params[1]) != NULL || params[1] == get_client(params[1])->getNickname())
            if (get_client(params[1]) != NULL )
            // if(params[1] == get_client(params[1])->getNickname())
            // if (get_client((nick) != NULL)
            {
                // if (check_client_in_channel(client->second, ch))
                // {

                // }
                // else
                // {

                    
                // }
                std::cout << " **************** tous valide **********  " << std::endl;
                
            }
            else
            {
                std::cout << "Invalid user  " << std::endl;
            }
        // }
        // else
        // {
        //     std::cout << "Invalid operateur " << std::endl;
        // }
        
    }
    else
    {
        std::cout << "Invalid chanel " << std::endl;
    }
}

// void server::invite(std::vector<std::string> params, std::map<int, client>::iterator client)
// {
//     (void)params;(void)client;
//     std::cout << "INVITE command called\n";
//     std::string nick = params[1];

//     int channelExist = findChannelByName(params[2], client->second);
//     // std::string userExist = findUserByName(params[1]);
//     // std::cout << "channel check ==" << ch->getName() << "\n";
//     // if (ch != NULL)
//     // if (ch != NULL || params[2] == ch->getName())
//     if (channelExist)
//     {
//         Channels *ch = getChannel(params[2]);
//         // if (client->second.getNickname() == ch->getOwnerNickname())
//         // {
//             // if (get_client(params[1]) != NULL || params[1] == get_client(params[1])->getNickname())
//             if (get_client(params[1]) != NULL )
//             // if(params[1] == get_client(params[1])->getNickname())
//             // if (get_client((nick) != NULL)
//             {
//                 // if (check_client_in_channel(client->second, ch))
//                 // {

//                 // }
//                 // else
//                 // {

                    
//                 // }
//                 std::cout << " **************** tous valide **********  " << std::endl;
                
//             }
//             else
//             {
//                 std::cout << "Invalid user  " << std::endl;
//             }
//         // }
//         // else
//         // {
//         //     std::cout << "Invalid operateur " << std::endl;
//         // }
        
//     }
//     else
//     {
//         std::cout << "Invalid chanel " << std::endl;
//     }
// }
