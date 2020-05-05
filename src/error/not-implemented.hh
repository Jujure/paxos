#pragma once

#include <stdexcept>

namespace http
{
    class NotImplemented : public std::logic_error
    {
    public:
        NotImplemented()
            : std::logic_error{"not implemented exception"}
        {}
        virtual ~NotImplemented() = default;
    };
} // namespace http
