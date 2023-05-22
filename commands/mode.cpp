/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:06:40 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/22 20:08:55 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void server::mode(std::vector<std::string> params, std::map<int, client>::iterator client) {
    
    if (params.size() < 3)
    {
        client->second.response(ERR_NEEDMOREPARAMS(client->second.getNickname()));
        return ;
    }
    
    std::string modes = params[2];
    Channels *ch = getChannel(params[1]);
    if (ch != NULL)
    {
        std::vector<std::pair<class::client, ROLE> > members = ch->getMembers();
        
        if (checkUserIsInChannel(client->second, ch) 
            && checkUserIsInChannel(client->second, ch)->second == OPERATOR)
        {     
            if (modes[0] == '+')
            {
                int i = 1;
                int k = 3;
                std::string mod = "+";
                std::string modeparams = "";
                bool invit = false, topic = false, key = false, owner = false, limit = false;
                
                while (i < (int)modes.size())
                {
                    if (modes[i] == 'i' && !invit)
                    {
                        ch->inviteOnly = true;
                        invit = true;
                    }
                    else if (modes[i] == 't' && !topic)
                    {
                        client->second.response("+t called");
                        
                        topic = true;
                    }
                    else if (modes[i] == 'k' && !key)
                    {
                        if (!params[k].empty())
                        {
                            ch->setKey(params[k]);
                            ch->isProtected = true;
                            mod += 'k';
                            modeparams += params[k] + " ";
                            k++;
                        }
                        else 
                            client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +k"));
                        key = true;
                    }
                    else if (modes[i] == 'o' && !owner)
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
                                    mod += 'o';
                                    modeparams += params[k] + " ";
                                    k++;
                                    owner = true;
                                }
                                else
                                    client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +o"));
                            }
                            else
                                client->second.responsefromServer(ERR_NOSUCHCHANNEL(client->second.getNickname(), params[k]));
                        }
                        
                    }
                    else if (modes[i] == 'l' && !limit)
                    {
                        if (!params[k].empty())
                        {
                            ch->setLimit(std::stoi(params[k]));
                            mod += 'l';
                            modeparams += params[k] + " ";
                            k++;
                        }
                        else
                            client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +l"));
                        limit = true;
                    }
                    else
                    {
                        client->second.responsefromServer(ERR_UNKNOWNMODE(client->second.getNickname(), modes[i]));
                    }

                    if (i == (int)modes.size() - 1 && (invit || topic || key || owner || limit))
                    {
                        send_to_clients(ch, client->second, "MODE " + ch->getName() + " " + mod + " " + modeparams);
                    }
                    i++;
                }
            }
            else if (modes[0] == '-')
            {
                int i = 1;
                while (i < (int)modes.size())
                {
                    if (modes[i] == 'i')
                    {
                        client->second.response("-i");
                    }
                    else if (modes[i] == 't')
                    {
                        client->second.response("-t");
                    }
                    else if (modes[i] == 'k')
                    {
                        client->second.response("-k");
                    }
                    else if (modes[i] == 'o')
                    {
                        client->second.response("-o");
                    }
                    else if (modes[i] == 'l')
                    {
                        client->second.response("-l");
                    }
                    else
                    {
                        client->second.response(ERR_UNKNOWNMODE(client->second.getNickname(), modes[i]));
                    }
                    i++;
                }
            }
            else 
                client->second.response(ERR_UNKNOWNMODE(client->second.getNickname(), modes));
        }
        else 
            client->second.responsefromServer(ERR_CHANOPRIVSNEEDED(client->second.getNickname(), params[1]));

    }
    else
        client->second.responsefromServer(ERR_NOSUCHCHANNEL(client->second.getNickname(), params[1]));

}