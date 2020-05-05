#include "addrinfo-error.hh"

namespace misc
{
    const std::error_category& addrinfo_category()
    {
        static addrinfo_error_category instance;
        return instance;
    }
} // namespace misc

inline std::error_code std::make_error_code(misc::addrinfo_error e)
{
    return std::error_code(static_cast<int>(e), misc::addrinfo_category());
}
