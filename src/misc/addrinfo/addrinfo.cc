#include "addrinfo.hh"

namespace misc
{
    AddrInfo getaddrinfo(const char* node, const char* service,
                         const AddrInfoHint& hints)
    {
        struct addrinfo* res;

        auto rc = ::getaddrinfo(node, service, &hints, &res);
        if (rc)
            throw std::system_error(rc, addrinfo_error_category(),
                                    "getaddrinfo");

        return AddrInfo(res);
    }
} // namespace misc

std::ostream& operator<<(std::ostream& os, const addrinfo&)
{
    os << "addrinfo{"
       << "}";
    return os;
}
