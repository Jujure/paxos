#include <arpa/inet.h>
#include <iostream>
#include <fstream>

#include "config.hh"
#include "parse.hh"

namespace paxos
{

    ServerConfig::ServerConfig(const std::vector<LegislatorConfig>& legislators,
            const LegislatorConfig& self)
        : legislators_(legislators), self_(self)
    {
    }

    static std::string format_ip(std::string ip)
    {
        int family = 0;

        /* Check if it is an IPv4 or Ipv6 address */
        if (ip.find(":") != std::string::npos)
            family = AF_INET6;
        else
            family = AF_INET;

        /* Allocated static buffer to make conversion */
        unsigned char buf[sizeof(struct in6_addr)];
        char formatted_ip[INET6_ADDRSTRLEN];

        /* Convert ip string to network address structure */
        int success = inet_pton(family, ip.c_str(), buf);

        if (success <= 0)
            error_and_exit(1, "parse_configuration: " + ip + " is an invalid ip");

        /* Convert back the network address to an string */
        inet_ntop(family, buf, formatted_ip, INET6_ADDRSTRLEN);
        return formatted_ip;
    }


    static void parse_mandatory_keys(const json& j, LegislatorConfig& config)
    {
        int port_int;

        safe_get_key(j, "ip", config.ip, true);
        config.ip = format_ip(config.ip);

        safe_get_key(j, "port", port_int, true);
        config.port = std::to_string(port_int);

        safe_get_key(j, "name", config.name, true);

        safe_get_key(j, "self", config.is_self, true);
    }


    static void from_json(const json& j, LegislatorConfig& config)
    {
        parse_mandatory_keys(j, config);
    }


    static std::pair<std::vector<LegislatorConfig>, LegislatorConfig>
        parse_legislators(const json& j)
    {
        /* Get 'vhosts' value */
        std::vector<json> legislators;
        safe_get_key(j, "legislators", legislators, true);

        /* Create VHostConfig vector and fill with VHostConfig */
        std::vector<LegislatorConfig> legislator_configs;
        LegislatorConfig self;

        for (auto it : legislators)
        {
            /* Differenciable vhost checking */
            auto legislator = it.get<paxos::LegislatorConfig>();
            if (!legislator.is_self)
                legislator_configs.push_back(legislator);
            else
                self = legislator;
        }

        return std::pair<std::vector<LegislatorConfig>, LegislatorConfig>
            (legislator_configs, self);
    }


    ServerConfig ServerConfig::parse(const std::string& path)
    {
        json json_dict;
        std::ifstream json_file(path);

        /* Check if file is corretly opened */
        if (!json_file.is_open())
        {
            error_and_exit(1, "parse_configuration: file " + path
                    + " doesn't exist.");
        }


        /* Check if file respect the json syntax */
        try
        {
            json_file >> json_dict;
        }
        catch (const nlohmann::detail::parse_error& e)
        {
            error_and_exit(1, e.what());
        }

        auto legislators = parse_legislators(json_dict);

        return ServerConfig(legislators.first, legislators.second);
    }
}
