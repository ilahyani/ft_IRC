/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:25:56 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/16 18:11:25 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "Channels.hpp"

Channels::Channels() {}

Channels::Channels(std::string name, std::string key, client Owner) {}

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

const std::map<int , client>&   Channels::getMembers() {
    return _channelMembers;
}
