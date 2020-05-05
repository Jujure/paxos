#include <iostream>

#include "config/config.hh"
#include "legislator/legislator-factory.hh"


int main(int, char **argv)
{
    paxos::ServerConfig server_config = paxos::ServerConfig::parse(argv[1]);

    for (auto config : server_config.legislators_)
    {
        paxos::LegislatorFactory::Create(config);
    }
}
