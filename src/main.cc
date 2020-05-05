#include <iostream>
#include <vector>

#include "config/config.hh"
#include "legislator/legislator-factory.hh"
#include "events/register.hh"
#include "misc/logger.hh"

paxos::EventWatcherRegistry paxos::event_register;
std::vector<paxos::shared_legislator> paxos::legislators;
paxos::shared_legislator paxos::self;

ev_signal sigint_watcher;
static void sigint_cb(struct ev_loop* loop, ev_signal*, int)
{
    ev_break(loop, EVBREAK_ALL);
}

ev_signal sigstop_watcher;
static void sigstop_cb(struct ev_loop*, ev_signal*, int)
{
    log("SIGSTOP detected trying to initiate ballot", paxos::red);
    paxos::self->initiate_ballot();
}


int main(int, char **argv)
{
    paxos::ServerConfig server_config = paxos::ServerConfig::parse(argv[1]);

    ev_signal_init(&sigint_watcher, sigint_cb, SIGINT);
    paxos::event_register.get_event_loop().register_sigint_watcher(&sigint_watcher);

    ev_signal_init(&sigstop_watcher, sigstop_cb, SIGTSTP);
    paxos::event_register.get_event_loop().register_sigint_watcher(&sigstop_watcher);

    paxos::self = paxos::LegislatorFactory::Create(server_config.self_);

    for (auto config : server_config.legislators_)
    {
        paxos::legislators.push_back(paxos::LegislatorFactory::Create(config));
    }
    
    paxos::event_register.get_event_loop()();
    return 0;
}
