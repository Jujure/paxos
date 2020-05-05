#include <iostream>

#include "config/config.hh"


int main(int, char **argv)
{
    paxos::ServerConfig config = paxos::ServerConfig::parse(argv[1]);
    std::cout << config.legislators_[0].name << "\n";
}
