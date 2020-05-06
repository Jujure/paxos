#pragma once

#include <stdexcept>
#include <string>
#include <system_error>

namespace paxos
{
    struct ConnectionFailed : public std::system_error
    {
        explicit ConnectionFailed()
            : std::system_error{errno, std::system_category()}
        {}
    };
} //namespace paxos
