#pragma once
#include "law/decree.hh"

namespace paxos
{
    struct Vote
    {
        std::string legislator;
        int ballot_id;
        Decree decree;
    };
}
