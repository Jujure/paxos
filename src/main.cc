#include <iostream>

#include "config/config.hh"
#include "legislator/legislator-factory.hh"
#include "events/register.hh"

paxos::EventWatcherRegistry paxos::event_register;

ev_signal sigint_watcher;
static void sigint_cb(struct ev_loop* loop, ev_signal*, int)
{
    ev_break(loop, EVBREAK_ALL);
}


int main(int, char **argv)
{
    paxos::ServerConfig server_config = paxos::ServerConfig::parse(argv[1]);

    ev_signal_init(&sigint_watcher, sigint_cb, SIGINT);
    paxos::event_register.get_event_loop().register_sigint_watcher(&sigint_watcher);

    paxos::LegislatorFactory::Create(server_config.self_);

    for (auto config : server_config.legislators_)
    {
        paxos::LegislatorFactory::Create(config);
    }
    
    paxos::event_register.get_event_loop()();
    return 0;
}
