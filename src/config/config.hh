#pragma once

#include<iostream>
#include <string>
#include "misc/json.hh"

namespace paxos
{
    struct LegislatorConfig
    {
        std::string ip;
        std::string port;
        std::string name;
        bool is_self;
    };

    struct ServerConfig
    {
        ServerConfig(const std::vector<LegislatorConfig>& legislators,
                const LegislatorConfig& self);

        std::vector<LegislatorConfig> legislators_;

        LegislatorConfig self_;

        static ServerConfig parse(const std::string& path);
    };
}