#pragma once
#include "legislator.hh"
#include "law/decree.hh"

namespace paxos
{
    struct Vote
    {
        Legislator legislator;
        int ballot_id;
        Decree decree;
    };
}
