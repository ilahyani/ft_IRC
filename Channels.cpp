#include "Channels.hpp"

Channels::Channels() {}

Channels::Channels(std::string name, std::string key, client& owner): _channelName(name), _channelKey(key) {
    addMember(owner, OPERATOR);
    isProtected = true;
    inviteOnly = false;
    topic = false;
    setLimit(500);
}

Channels::Channels(std::string name, client& owner): _channelName(name) {
    addMember(owner, OPERATOR);
    isProtected = false;
    inviteOnly = false;
    topic = false;
    setLimit(500);
}

Channels::~Channels() {}

const std::string&  Channels::getName() {
    return _channelName;
}

void Channels::setName(std::string name) {
    _channelName = name;
}

const std::string&  Channels::getKey() {
    return _channelKey;
}

void Channels::setKey(std::string key) {
    _channelKey = key;
}

const std::string&  Channels::geTopic() {
    return _channelTopic;
}
   
void Channels::setTopic(std::string topic) {
    _channelTopic = topic;
}

const int& Channels::getLimit(){
    return _channelLimit;
}

void Channels::setLimit(int limit){
    _channelLimit = limit;
}

std::vector<std::pair<client, ROLE> >& Channels::getMembers() {
    return _Members;
}

void Channels::addMember(client& member, ROLE role) {
    _Members.push_back(std::make_pair(member, role));
}

void Channels::addToListInvite(client& member){
    _MembersInvite.push_back(member);
}

std::vector<client>& Channels::getMembersInvite(){
    return _MembersInvite;
}

bool Channels::checkIsInvited(client* c)
{
    std::vector<client>::iterator it = _MembersInvite.begin();
    while (it != _MembersInvite.end())
    {
        if (it->getsocket() == c->getsocket())
        {
            _MembersInvite.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

void Channels::removeMember(client &c)
{
    std::vector<std::pair<client, ROLE> >::iterator it = _Members.begin();
    while (it != _Members.end())
    {
        if (it->first.getsocket() == c.getsocket())
        {
            _Members.erase(it);
            return ;
        }
        it++;
    }
}