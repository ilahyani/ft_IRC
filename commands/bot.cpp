/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:15:34 by ilahyani          #+#    #+#             */
/*   Updated: 2023/06/02 17:50:52 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

std::string getMonthStartDate()
{
    std::stringstream year, month, day;
    std::time_t now = std::time(NULL);
    std::tm *local_time = std::localtime(&now);

    local_time->tm_mday = 1;
    std::time_t first_day_of_month = std::mktime(local_time);
    std::tm *first_day_local_time = std::localtime(&first_day_of_month);
    year << first_day_local_time->tm_year + 1900;
    month << first_day_local_time->tm_mon + 1;
    day << first_day_local_time->tm_mday;
    return year.str() + "-" + month.str() + "-" + day.str();
}

void trimString(std::string &str)
{
    str.erase(str.begin());
    str.erase(str.end() - 1);
}

std::string getAPItoken()
{
    static std::string apiToken;
    static std::time_t lastGenerated = 0;
    std::string clientUid = "client_id=u-s4t2ud-91439faa9a64d4f05e4e686d7a2fec8f588f4503f200e6aed0ced25247d91991";
    std::string clientSecret = "client_secret=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";
    std::string apiURL = "https://api.intra.42.fr/oauth/token";
    std::string command = "curl -sS -X POST --data \"grant_type=client_credentials&" + clientUid + "&" + clientSecret + "\" " + apiURL;

    if ((std::time(NULL) - lastGenerated) < 7200)
        return apiToken;
    std::system((command + " > /tmp/.token").c_str());
    std::ifstream ifs("/tmp/.token");
    getline(ifs, apiToken, '\0');
    ifs.close();
    trimString(apiToken);
    apiToken = std::strtok(&apiToken[0], ",");
    apiToken = std::strtok(&apiToken[0], ":");
    apiToken = std::strtok(NULL, ":");
    trimString(apiToken);
    lastGenerated = std::time(NULL);
    return apiToken;
}

std::string calculateLogtime(std::vector<std::string> logtimeData)
{
    double logtime = 0;
    std::stringstream ss;

    for (size_t i = 0; i < logtimeData.size(); i++)
    {
        logtime += std::atoi(logtimeData[i].substr(0, 2).c_str()) * 60;
        logtime += std::atoi(logtimeData[i].substr(3, logtimeData[i].size()).c_str());
    }
    ss << static_cast<int>(logtime / 60);
    return ss.str();
}

std::vector<std::string> fetchLogtimeData(std::string date, std::string API_TOKEN, std::string login)
{
    std::vector<std::string> logtime;
    std::string apiURL = "\" \"https://api.intra.42.fr/v2/users/" + login + "/locations_stats?begin_at=";
    std::string command = "curl -Ss -H \"Authorization: Bearer " + API_TOKEN + apiURL + date + "\"";
    std::string logtimeData;
    std::ifstream ifs;
    char *token;

    std::system((command + " > /tmp/data.json").c_str());
    ifs.open("/tmp/data.json");
    getline(ifs, logtimeData, '\0');
    ifs.close();
    if (logtimeData == "{}")
        return logtime;
    trimString(logtimeData);
    token = std::strtok(&logtimeData[0], ",");
    while (token != NULL)
    {
        std::string tmp(token);
        size_t startPos = tmp.find_first_of(':') + 2;
        size_t endPos = tmp.find_last_of(':') - (tmp.find_first_of(':') + 2);
        logtime.push_back(tmp.substr(startPos, endPos));
        token = std::strtok(NULL, ",");
    }
    return logtime;
}

void server::bot(std::vector<std::string> params, std::map<int, client>::iterator client)
{
    // (void)client;
    std::vector<std::string> logtime;
    std::string date;

    if (params.size() > 1)
    {
        std::string login = params[1];
        date = getMonthStartDate();
        logtime = fetchLogtimeData(date, getAPItoken(), login);
        if (logtime.empty())
            client->second.print("There is no user with login: " + login);
        else
        {
            std::string response = login + "\' logtime for this month is: " + calculateLogtime(logtime) + " Hours 🤝";
            client->second.print(response);
        }
        return;
    }
    client->second.print("Hmm.. something went wrong, are you sure you entered the right parameters?");
}
