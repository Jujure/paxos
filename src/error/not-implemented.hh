#pragma once

#include <stdexcept>

namespace paxos
{
    class NotImplemented : public std::logic_error
    {
    public:
        NotImplemented()
            : std::logic_error{"not implemented exception"}
        {}
        virtual ~NotImplemented() = default;
    };
} // namespace paxos
