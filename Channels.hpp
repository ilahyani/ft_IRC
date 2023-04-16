/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:23:34 by ilahyani          #+#    #+#             */
/*   Updated: 2023/04/16 18:11:48 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "client.hpp"

typedef std::string                    String;
typedef std::map<int , client>         Map;
class Channels
{
    String                  _channelName;
    String                  _channelTopic;
    String                  _channelKey;
    std::map<int , client>  _channelOperators;
    std::map<int , client>  _channelMembers;
    client                  _channelOwner;
    public:
        Channels();
        Channels(std::string name, std::string key, client owner);
        Channels(std::string name, client owner);
        ~Channels();

        bool                            isProtected;

        const std::string&              getName();
        void                            setName(std::string name);
        const std::string&              getKey();
        void                            setKey(std::string key);
        const std::string&              geTopic();   
        void                            setTopic(std::string topic);
        const std::map<int , client>&   getMembers();

        // void                            addMember(client& client, bool makeOperator);
        // void                            RemoveMember(client& client);
        // bool                            checkKey(std::string key);
};