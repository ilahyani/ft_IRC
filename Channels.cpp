/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:25:56 by ilahyani          #+#    #+#             */
/*   Updated: 2023/05/07 00:40:35 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "Channels.hpp"

Channels::Channels() {}

Channels::Channels(std::string name, std::string key, client& owner)
    : _channelName(name), _channelKey(key), _channelOwner(owner) {
        isProtected = true;
    }

Channels::Channels(std::string name, client& owner)
    : _channelName(name), _channelOwner(owner) {
        isProtected = false;
    }

Channels::~Channels() {}

const std::string&  Channels::getName() {
    return _channelName;
}

void    Channels::setName(std::string name) {
    _channelName = name;
}

const std::string&  Channels::getKey() {
    return _channelKey;
}

void    Channels::setKey(std::string key) {
    _channelKey = key;
}

const std::string&  Channels::geTopic() {
    return _channelTopic;
}
   
void    Channels::setTopic(std::string topic) {
    _channelTopic = topic;
}

const std::vector<client>&   Channels::getMembers() {
    return _channelMembers;
}

void    Channels::addMember(client& member, bool makeOperator) {
    _channelMembers.push_back(member);
    if (makeOperator) {
        member.isOpreator = true;
        _channelOperators.push_back(member);
    }
}

const std::string& Channels::getOwnerNickname()
{
    return _channelOwner.getNickname();
}

// void    Channels::removeMember(client& member) {
//     std::vector<client>::iterator it;

//     it = std::find(_channelMembers.begin(), _channelMembers.end(), member);
//     if (it != _channelMembers.end())
//         _channelMembers.erase(it);
//     it = std::find(_channelOperators.begin(), _channelOperators.end(), member);
//     if (it != _channelOperators.end())
//         _channelOperators.erase(it);
// }
