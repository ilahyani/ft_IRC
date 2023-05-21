#include "../server.hpp"

// void server::send_message_to_user(std::string nick, std::string message, client client)
// {
//     if (get_client(nick) == NULL || nick != get_client(nick)->getNickname())
//     {
//         client.response(ERR_NOSUCHNICK(client.getNickname()));
//         return ;
//     }
//     sendToClient(nick, nick, message, client, "NOTICE");
// }

// void server::send_message_to_channel(std::string channel, std::string message, client c)
// {
//     Channels *ch = getChannel(channel);
//     if (ch == NULL || channel != ch->getName())
//     {
//         c.response(ERR_NOSUCHCHANNEL(c.getNickname(), channel));
//         return ;
//     }

//     std::vector<client> members = ch->getMembers();
//     for (int i = 0; i < (int)members.size(); i++)
//     {
//         if (members[i].getNickname() == c.getNickname())
//             i++;
//         if ((int)members.size() == i)
//             break;
//         sendToClient(members[i].getNickname(), channel, message, c, "NOTICE");
//     }
//     if (c.getNickname() != ch->getOwnerNickname())
//         sendToClient(ch->getOwnerNickname(), channel, message, c, "NOTICE");
// }

// void server::notice(std::vector<std::string> params, std::map<int, client>::iterator client) {
    
//     if (params.size() < 3)
//     {
//         client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
//         return ;
//     }
    
//     if (params[1][0] == '#')
//         send_message_to_channel(params[1], params[2], client->second);
//     else
//         send_message_to_user(params[1], params[2], client->second);
// }
 void server::notice(std::vector<std::string> params, std::map<int, client>::iterator client) {
    
    // if (params.size() < 3)
    // {
    //     client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
    //     return ;
    // }
    
    // if (params[1][0] == '#')
    //     send_message_to_channel(params[1], params[2], client->second);
    // else
    //     send_message_to_user(params[1], params[2], client->second);

    (void)params, (void) client;
}