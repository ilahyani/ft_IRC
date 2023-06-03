#pragma once

#include "irc.hpp"
#include "client.hpp"

enum ROLE { OPERATOR, MEMBER };

class Channels
{
    std::string                            _channelName;
    std::string                            _channelTopic;
    std::string                            _channelKey;
    std::vector<std::pair<client, ROLE> >  _Members;
    std::vector<client>                    _MembersInvite;
    std::vector<client>                    _MembersBan;
    int                                    _channelLimit;
    public:
        bool    isProtected;
        bool    inviteOnly;
        bool    topic;

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
        bool                  checkIsInvited(client* c);
        void                  addToListInvite(client& member);
        void                  removeMember(client &c);
};  