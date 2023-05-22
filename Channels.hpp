/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:23:34 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/22 23:31:08 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "client.hpp"

enum ROLE { OPERATOR, MEMBER };

class Channels
{
    std::string                            _channelName;
    std::string                            _channelTopic;
    std::string                            _channelKey;
    int                                    _channelLimit;
    std::vector<std::pair<client, ROLE> >  _Members;

    std::vector<client>                    _MembersInvite;
    std::vector<client>                    _MembersBan;

    public:
        bool    isProtected;
        bool    inviteOnly;

        Channels();
        Channels(std::string name, std::string key, client& owner);
        Channels(std::string name, client& owner);
        ~Channels();
        const std::string&    getName();
        const std::string&    getKey();
        const std::string&    geTopic();
        const int&            getLimit();
        std::vector<client>&  getMembersInvite();
        void                  setName(std::string name);
        void                  setKey(std::string key);
        void                  setTopic(std::string topic);
        void                  setLimit(int);
        void                  addMember(client& , ROLE);
        std::vector<std::pair<client, ROLE> >& getMembers();
        client* checkIsInvited(client* c);
        void addToListInvite(client& member);
        // void                removeMember(client& member);
        // bool                checkKey(std::string key);
};  