#pragma once

#include <stdexcept>
#include <string>
#include <system_error>

namespace paxos
{
    struct ConnectionRecvClosedError: public std::system_error
    {
        explicit ConnectionRecvClosedError()
            : std::system_error{errno, std::system_category()}
        {}
    };
} //namespace paxos
