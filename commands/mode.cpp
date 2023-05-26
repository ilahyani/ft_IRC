/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:06:40 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/26 22:38:24 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

int ft_skip_double_sign(std::string modes)
{
    int i = (int)modes.size();
    while (i > 0)
    {
        if (modes[i] == '-' || modes[i] == '+')
            return (i);
        i--;
    }
    return (i);
}

bool ft_check_modes(char c)
{
    std::string str = "itkol";
    int i = 0;
    while (i < (int)str.size())
    {
        if (c == str[i])
            return true;
        i++;
    }
    return false;
}

std::string parse_modes(std::string _str)
{
    std::string modes;
    std::string str = "+" + _str;
    int i = 0;
    while (str[i])
    {
        while (str[i] == '+' || str[i] == '-') 
            i++;
        if (str[i - 1] == '+' || str[i - 1] == '-')
        {
            if (str[i] == '\0')
            {
                if (modes.size() && (modes[modes.size() - 1] == '+' || modes[modes.size() - 1] == '-'))
                    modes[modes.size() - 1] = '\0';
                return modes;
            }
            else if (modes.size() && (modes[modes.size() - 1] == '+' || modes[modes.size() - 1] == '-'))
                modes[modes.size() - 1] = str[i - 1];
            else
                modes.push_back(str[i - 1]);
        }
        if (modes.find(str[i]) == std::string::npos)
            modes.push_back(str[i]);
        i++;
    }
    if (modes.size() && (modes[modes.size() - 1] == '+' || modes[modes.size() - 1] == '-'))
        modes[modes.size() - 1] = '\0';
    return modes;
}

void server::mode_plus(int &k, std::string &execMode, std::string &modeparams,std::string modex, Channels *ch, std::vector<std::string> params, std::map<int, client>::iterator client)
{
    execMode.push_back('+');
    for (size_t i = 1; i < modex.size(); i++)
    {
        if (modex[i] == 'i')
        {
            ch->inviteOnly = true;
            execMode.push_back('i');
        }
        else if (modex[i] == 't')
        {
            if (!params[k].empty())
            {
                ch->setTopic(params[k]);
                execMode.push_back('t');
                modeparams += params[k] + " ";
                k++;
            }
            else
                client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +t"));
        }
        else if (modex[i] == 'k')
        {
            if (!params[k].empty())
            {
                ch->setKey(params[k]);
                ch->isProtected = true;
                execMode.push_back('k');
                modeparams += params[k] + " ";
                k++;
            }
            else
                client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +k"));
        }
        else if (modex[i] == 'o')
        {
            if (!params[k].empty())
            {
                class::client *c = get_client(params[k]);
                if (c)
                {
                    std::pair<class::client, ROLE>* clientinchannel = checkUserIsInChannel(*c, ch);
                    if (clientinchannel)
                    {
                        std::vector<std::pair<class::client, ROLE> >::iterator it = ch->getMembers().begin();
                        while (it != ch->getMembers().end())
                        {
                            if (clientinchannel->first.getsocket() == it->first.getsocket())
                                it->second = OPERATOR;
                            it++;
                        }
                        execMode.push_back('o');
                        modeparams += params[k] + " ";
                    }
                }
                else
                    client->second.responsefromServer(ERR_NOSUCHNICK(client->second.getNickname(), params[k]));
                k++;
            }
            else
                client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +o"));
        }
        else if (modex[i] == 'l')
        {
            if (!params[k].empty())
            {
                for(int i = 0; i < (int)params[k].size(); i++)
                {
                    if (!isdigit(params[k][i]))
                        return ;
                }
                ch->setLimit(std::stoi(params[k]));
                execMode.push_back('l');
                modeparams += params[k] + " ";
                k++;
            }
            else
                client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +l"));
        }
        else
            client->second.responsefromServer(ERR_UNKNOWNMODE(client->second.getNickname(), modex[i]));
    }
    if (execMode[execMode.size() - 1] == '+')
        execMode.erase(execMode.end() - 1);
}

void server::mode(std::vector<std::string> params, std::map<int, client>::iterator client) {
    if (params.size() < 3)
    {
        client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }
    std::string modes = parse_modes(params[2]);
    std::cout << modes << "\n";
    Channels *ch = getChannel(params[1]);
    if (!ch)
    {
        client->second.responsefromServer(ERR_NOSUCHCHANNEL(client->second.getNickname(), params[1]));
        return;   
    }
    std::vector<std::pair<class::client, ROLE> > members = ch->getMembers();
    if (!checkUserIsInChannel(client->second, ch) 
        || checkUserIsInChannel(client->second, ch)->second != OPERATOR)
    {
        client->second.responsefromServer(ERR_CHANOPRIVSNEEDED(client->second.getNickname(), params[1]));
        return ;
    }
    size_t pos_start = 1;
    size_t pos_m = 0;
    size_t pos_p = 0;
    
    std::string modex;
    std::string execMode, modeparams;
    int k = 3;
    std::cout << "starting\n";
    while (1)
    {
        pos_m = modes.find('-', pos_start);
        pos_p = modes.find('+', pos_start);
        if (pos_m > pos_p)
        {
            modex = modes.substr(pos_start - 1, pos_p - (pos_start - 1));
            std::cout << modex << "\n";
            
            if (modex[0] == '+')
                mode_plus(k, execMode, modeparams, modex, ch, params, client);
            pos_start = pos_p + 1;
        }
        else
        {
            modex = modes.substr(pos_start - 1, pos_m - (pos_start - 1));
            std::cout << modex << "\n";
            if (modex[0] == '+')
                mode_plus(k, execMode, modeparams, modex, ch, params, client);
            pos_start = pos_m + 1;           
        }
        if (pos_start - 1 == std::string::npos)
            break;
    }
    if (execMode[0])
        send_to_clients(ch, client->second, "MODE " + ch->getName() + " " + execMode + " " + modeparams);
    modeparams.clear();
    execMode.clear();
}


// void server::mode(std::vector<std::string> params, std::map<int, client>::iterator client) {
    
//     if (params.size() < 3)
//     {
//         client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
//         return ;
//     }
    
//     std::string modes = parse_modes(params[2]);
//     std::cout << modes << "\n";
//     Channels *ch = getChannel(params[1]);
//     if (ch != NULL)
//     {
//         std::vector<std::pair<class::client, ROLE> > members = ch->getMembers();
//         if (checkUserIsInChannel(client->second, ch) 
//             && checkUserIsInChannel(client->second, ch)->second == OPERATOR)
//         {
//             int i = 0;
//             if (modes[i] == '+')
//             {
//                 i++;
//                 int k = 3;
//                 std::string mod = "+";
//                 std::string modeparams;
//                 bool invit = false, topic = false, key = false, owner = false, limit = false;
//                 while (i < (int)modes.size())
//                 {
//                     if (ft_check_modes(modes[i]))
//                     {
//                         if (modes[i] == 'i' && !invit)
//                         {
//                             ch->inviteOnly = true;
//                             mod += 'i';
//                             invit = true;
//                         }
//                         else if (modes[i] == 't' && !topic)
//                         {
//                             if (!params[k].empty())
//                             {
//                                 ch->setTopic(params[k]);
//                                 mod += 't';
//                                 modeparams += params[k] + " ";
//                                 k++;
//                             }
//                             else
//                                 client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +t"));
//                             topic = true;
//                         }
//                         else if (modes[i] == 'k' && !key)
//                         {
//                             if (!params[k].empty())
//                             {
//                                 ch->setKey(params[k]);
//                                 ch->isProtected = true;
//                                 mod += 'k';
//                                 modeparams += params[k] + " ";
//                                 k++;
//                             }
//                             else if (params[k].empty() && !key)
//                                 client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +k"));
//                             key = true;
//                         }
//                         else if (modes[i] == 'o' && !owner)
//                         {
//                             if (!params[k].empty())
//                             {
//                                 class::client *c = get_client(params[k]);
//                                 if (c)
//                                 {
//                                     std::pair<class::client, ROLE>* clientinchannel = checkUserIsInChannel(*c, ch);
//                                     if (clientinchannel)
//                                     {
//                                         std::vector<std::pair<class::client, ROLE> >::iterator it = ch->getMembers().begin();
//                                         while (it != ch->getMembers().end())
//                                         {
//                                             if (clientinchannel->first.getsocket() == it->first.getsocket())
//                                                 it->second = OPERATOR;
//                                             it++;
//                                         }
//                                         mod += 'o';
//                                         modeparams += params[k] + " ";
//                                         k++;
                                        
//                                     }
//                                 }
//                                 else
//                                     client->second.responsefromServer(ERR_NOSUCHNICK(client->second.getNickname(), params[k]));
//                             }
//                             else
//                                 client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +o"));
//                             owner = true;
//                         }
//                         else if (modes[i] == 'l' && !limit)
//                         {
//                             if (!params[k].empty())
//                             {
//                                 for(int i = 0; i < (int)params[k].size(); i++)
//                                 {
//                                     if (!isdigit(params[k][i]))
//                                         return ;
//                                 }
//                                 ch->setLimit(std::stoi(params[k]));
//                                 mod += 'l';
//                                 modeparams += params[k] + " ";
//                                 k++;
//                             }
//                             else
//                                 client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +l"));
//                             limit = true;
//                         }
//                     }
//                     else
//                         client->second.responsefromServer(ERR_UNKNOWNMODE(client->second.getNickname(), modes[i]));

//                     if (i == (int)modes.size() - 1 && (invit || topic || key || owner || limit))
//                     {
//                         send_to_clients(ch, client->second, "MODE " + ch->getName() + " " + mod + " " + modeparams);
//                         modeparams.clear();
//                     }
//                     i++;
//                 }
//             }
//             else if (modes[i] == '-')
//             {
//                 i++;
//                 std::string mod = "-";
//                 bool invit = false, topic = false, key = false, owner = false, limit = false;
//                 while (i < (int)modes.size())
//                 {
//                     if (modes[i] == 'i' && !invit)
//                     {
//                         ch->inviteOnly = false;
//                         mod += "i";
//                         invit = true;
//                     }
//                     else if (modes[i] == 't' && !topic)
//                     {
//                         client->second.response("-t");
//                     }
//                     else if (modes[i] == 'k' && !key)
//                     {
//                         ch->isProtected = false;
//                         ch->setKey("");
//                         mod += "k";
//                         key = true;
//                     }
//                     else if (modes[i] == 'o' && !owner)
//                     {
//                         client->second.response("-o");
//                     }
//                     else if (modes[i] == 'l' && !limit)
//                     {
//                         ch->setLimit(500);
//                         mod += "l";
//                         limit = true;
//                     }
//                     else
//                     {
//                         client->second.response(ERR_UNKNOWNMODE(client->second.getNickname(), modes[i]));
//                     }
//                     if (i == (int)modes.size() - 1 && (invit || topic || key || owner || limit))
//                     {
//                         send_to_clients(ch, client->second, "MODE " + ch->getName() + " " + mod);
//                     }
//                     i++;
//                 }
//             }
//             else 
//                 client->second.response(ERR_UNKNOWNMODE(client->second.getNickname(), modes));
//         }
//         else 
//             client->second.responsefromServer(ERR_CHANOPRIVSNEEDED(client->second.getNickname(), params[1]));

//     }
//     else
//         client->second.responsefromServer(ERR_NOSUCHCHANNEL(client->second.getNickname(), params[1]));

// }