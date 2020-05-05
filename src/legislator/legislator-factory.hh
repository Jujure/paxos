#pragma once

#include "legislator.hh"
#include "config/config.hh"

namespace paxos
{
    class LegislatorFactory
    {
    public:
        static shared_legislator Create(LegislatorConfig& config);
    };
}
