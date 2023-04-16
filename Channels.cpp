/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:25:56 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/16 18:40:44 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "Channels.hpp"

Channels::Channels() {}

Channels::Channels(std::string name, std::string key, client owner)
    : _channelName(name), _channelKey(key), _channelOwner(owner) {
        isProtected = true;
    }

Channels::Channels(std::string name, client owner)
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

void    Channels::addMember(client& client, bool makeOperator) {
    _channelMembers.push_back(client);
    if (makeOperator) {
        client.isOpreator = true;
        _channelOperators.push_back(client);
    }
}
