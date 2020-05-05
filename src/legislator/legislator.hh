#pragma once
#include "config/config.hh"

namespace paxos
{
    class Legislator
    {
    public:
        Legislator(const LegislatorConfig& config);
        LegislatorConfig config_;

    };
    using shared_legislator = std::shared_ptr<Legislator>;
}
