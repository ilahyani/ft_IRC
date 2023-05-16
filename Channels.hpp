/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:23:34 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/15 18:55:29 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "client.hpp"

class Channels
{
    std::string             _channelName;
    std::string             _channelTopic;
    std::string             _channelKey;
    std::vector<client>     _channelOperators;
    std::vector<client>     _channelMembers;
    client                  _channelOwner;
    public:
        Channels();
        Channels(std::string name, std::string key, client& owner);
        Channels(std::string name, client& owner);
        ~Channels();

        bool                            isProtected;

        const std::string&              getName();
        void                            setName(std::string name);
        const std::string&              getKey();
        void                            setKey(std::string key);
        const std::string&              geTopic();   
        void                            setTopic(std::string topic);
        const std::vector<client>&      getMembers();
        void                            addMember(client& member, bool makeOperator);
        const std::string&              getOwnerNickname();
        void                            setOwner(client client);
        const client&                   getOwner();
        // void                            removeMember(client& member);
        // bool                            checkKey(std::string key);
};