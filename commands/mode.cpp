/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:06:40 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/30 22:27:21 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

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

void server::mode_plus(int &k, std::string &execMode, std::string &modeparams,std::string modex, Channels *ch, 
    std::vector<std::string> params, std::map<int, client>::iterator cl, client* client_mode)
{
    execMode.push_back('+');
    for (size_t i = 1; i < modex.size(); i++)
    {
        if (modex[i] && client_mode)
        {
            if (modex[i] == 'w')
            {
                client_mode->wallops = true;
                execMode.push_back('w');
            }
            else if (modex[i] == 'i')
            {
                client_mode->isInvisible = true;
                execMode.push_back('i');
            }
        }
        else if (modex[i] && ch)
        {
            if (modex[i] == 'i' )
            {
                ch->inviteOnly = true;
                execMode.push_back('i');
            }
            else if (modex[i] == 't' )
            {
                ch->topic = true;
                execMode.push_back('t');
            }
            else if (modex[i] == 'k' )
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
                    cl->second.responsefromServer(ERR_NEEDMOREPARAMS(cl->second.getNickname() + " MODE +k"));
            }
            else if (modex[i] == 'o' )
            {
                if (!params[k].empty())
                {
                    client *c = get_client(params[k]);
                    if (c)
                    {
                        std::pair<client, ROLE>* clientinchannel = checkUserIsInChannel(*c, ch);
                        if (clientinchannel)
                        {
                            std::vector<std::pair<client, ROLE> >::iterator it = ch->getMembers().begin();
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
                        cl->second.responsefromServer(ERR_NOSUCHNICK(cl->second.getNickname(), params[k]));
                    k++;
                }
                else
                    cl->second.responsefromServer(ERR_NEEDMOREPARAMS(cl->second.getNickname() + " MODE +o"));
            }
            else if (modex[i] == 'l' )
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
                    cl->second.responsefromServer(ERR_NEEDMOREPARAMS(cl->second.getNickname() + " MODE +l"));
            }
        }
        else
            cl->second.responsefromServer(ERR_UNKNOWNMODE(cl->second.getNickname(), modex[i]));
    }
    if (execMode[execMode.size() - 1] == '+')
        execMode.erase(execMode.end() - 1);
}

void server::mode_minus(int &k, std::string &execMode, std::string &modeparams,std::string modex, Channels *ch, 
    std::vector<std::string> params, std::map<int, client>::iterator cl, client* client_mode)
{
    execMode.push_back('-');
    for (size_t i = 1; i < modex.size(); i++)
    {
        if (modex[i] && client_mode)
        {
            if (modex[i] == 'w')
            {
                execMode.push_back('w');
                client_mode->wallops = false;
            }
            else if (modex[i] == 'i')
            {
                client_mode->isInvisible = false;
                execMode.push_back('i');
            }
        }
        else if (modex[i] && ch)
        {
            if (modex[i] == 'i')
            {
                ch->inviteOnly = false;
                execMode.push_back('i');
            }
            else if (modex[i] == 't')
            {
                ch->topic = false;
                execMode.push_back('t');
            }
            else if (modex[i] == 'k')
            {
                ch->setKey("");
                ch->isProtected = false;
                execMode.push_back('k');
            }
            else if (modex[i] == 'o')
            {
                if (!params[k].empty())
                {
                    client *c = get_client(params[k]);
                    if (c)
                    {
                        std::pair<client, ROLE>* clientinchannel = checkUserIsInChannel(*c, ch);
                        if (clientinchannel)
                        {
                            std::vector<std::pair<client, ROLE> >::iterator it = ch->getMembers().begin();
                            while (it != ch->getMembers().end())
                            {
                                if (clientinchannel->first.getsocket() == it->first.getsocket())
                                    it->second = MEMBER;
                                it++;
                            }
                            execMode.push_back('o');
                            modeparams += params[k] + " ";
                        }
                    }
                    else
                        cl->second.responsefromServer(ERR_NOSUCHNICK(cl->second.getNickname(), params[k]));
                    k++;
                }
                else
                    cl->second.responsefromServer(ERR_NEEDMOREPARAMS(cl->second.getNickname() + " MODE -o"));
            }
            else if (modex[i] == 'l')
            {
                ch->setLimit(500);
                execMode.push_back('l');
            }
        }
        else
            cl->second.responsefromServer(ERR_UNKNOWNMODE(cl->second.getNickname(), modex[i]));
    }
    if (execMode[execMode.size() - 1] == '-')
        execMode.erase(execMode.end() - 1);
}

void server::mode(std::vector<std::string> params, std::map<int, client>::iterator cl) {
    if (params.size() == 2)
        return ;
    if (params.size() < 3)
    {
        cl->second.response(ERR_NEEDMOREPARAMS(cl->second.getNickname()));
        return ;
    }
    std::string modes = parse_modes(params[2]);
    Channels* ch = NULL;
    client* client_mode = NULL;
    if (params[1][0] == '#' && params.size() > 1)
    {
        ch = getChannel(params[1]);
        if (!ch)
        {
            cl->second.responsefromServer(ERR_NOSUCHCHANNEL(cl->second.getNickname(), params[1]));
            return;   
        }
        std::vector<std::pair<class::client, ROLE> > members = ch->getMembers();
        if (!checkUserIsInChannel(cl->second, ch) 
            || checkUserIsInChannel(cl->second, ch)->second != OPERATOR)
        {
            cl->second.responsefromServer(ERR_CHANOPRIVSNEEDED(cl->second.getNickname(), params[1]));
            return ;
        }
    }
    else
    {
        client_mode = get_client(params[1]);
        if (client_mode && client_mode->getNickname() != cl->second.getNickname())
        {
            cl->second.responsefromServer(ERR_USERSDONTMATCH(cl->second.getNickname()));
            return ;
        }
    }
        
    size_t pos_start = 1;
    size_t pos_m = 0;
    size_t pos_p = 0;
    int    k = 3;

    std::string modex;
    std::string execMode, modeparams;
    while (1 && modes[0])
    {
        pos_m = modes.find('-', pos_start);
        pos_p = modes.find('+', pos_start);
        if (pos_m > pos_p)
        {
            modex = modes.substr(pos_start - 1, pos_p - (pos_start - 1));
            if (modex[0] == '+')
                mode_plus(k, execMode, modeparams, modex, ch, params, cl, client_mode);
            else 
                mode_minus(k, execMode, modeparams, modex, ch, params, cl, client_mode);
            pos_start = pos_p + 1;
        }
        else
        {
            modex = modes.substr(pos_start - 1, pos_m - (pos_start - 1));
            if (modex[0] == '+')
                mode_plus(k, execMode, modeparams, modex, ch, params, cl, client_mode);
            else
                mode_minus(k, execMode, modeparams, modex, ch, params, cl, client_mode);
            pos_start = pos_m + 1;
        }
        if (pos_start - 1 == std::string::npos)
            break;
    }
    if (execMode[0] && client_mode)
        cl->second.responsefromServer(RPL_UMODEIS(cl->second.getNickname(), execMode));
    else if (execMode[0] && ch)
        send_to_all_in_channel(ch, cl->second, "MODE " + ch->getName() + " " + execMode + " " + modeparams);
    modeparams.clear();
    execMode.clear();
}