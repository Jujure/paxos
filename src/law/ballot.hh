#pragma once
#include <unordered_set>

#include "decree.hh"

namespace paxos
{
    struct Ballot
    {
        int id;
        Decree decree;
        std::unordered_set<std::string> quorum;
        std::unordered_set<std::string> voters;
    }
}
