/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:06:40 by kid-bouh          #+#    #+#             */
/*   Updated: 2023/05/21 04:45:07 by kid-bouh         ###   ########.fr       */
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
    if (ch)
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
                    client->second.response("+i called");
                    
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
                        key = true;
                    }
                    else 
                        client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +k"));
                }
                else if (modes[i] == 'o' && !owner)
                {
                    client->second.response("+o called");
                    owner = true;
                }
                else if (modes[i] == 'l' && !limit)
                {
                    if (!params[k].empty())
                    {
                        ch->setLimit(std::stoi(params[k]));
                        mod += 'l';
                        modeparams += params[k] + " ";
                        k++;
                        limit = true;
                    }
                    else
                        client->second.responsefromServer(ERR_NEEDMOREPARAMS(client->second.getNickname() + " MODE +l"));
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
        {
            client->second.response("ERROR");
        }
    }

}