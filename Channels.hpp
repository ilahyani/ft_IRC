/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:23:34 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/20 20:13:15 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "client.hpp"

enum ROLE { OPERATOR, MEMBER };

class Channels
{
    std::string             _channelName;
    std::string             _channelTopic;
    std::string             _channelKey;
    int                     _channelLimit;
    
    // std::vector<client>     _channelOperators;
    // std::vector<client>     _channelMembers;
    // client                  _channelOwner;
    
    std::vector<std::pair<client, ROLE> > _Members;
    public:
        Channels();
        Channels(std::string name, std::string key, client& owner);
        Channels(std::string name, client& owner);
        ~Channels();

        bool                            isProtected;
        bool                            inviteOnly;

        const std::string&              getName();
        void                            setName(std::string name);
        const std::string&              getKey();
        void                            setKey(std::string key);
        const std::string&              geTopic();
        void                            setTopic(std::string topic);
        const std::vector<std::pair<client, ROLE> >&  getMembers();
        void                            addMember(client& , ROLE);
        const int&                      getLimit();
        void                            setLimit(int);
        // void                            removeMember(client& member);
        // bool                            checkKey(std::string key);
};