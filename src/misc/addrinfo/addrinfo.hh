/**
 * \file misc/addrinfo/addrinfo.hh
 * \brief Structures used to wrap getaddrinfo(3).
 */
#pragma once

#include <cstring>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <utility>

#include "addrinfo-error.hh"
#include "addrinfo-iterator.hh"

namespace misc
{
    /**
     * \class AddrInfo
     * \brief Object representing list of network addresses (IP, Port, Host).
     */
    class AddrInfo
    {
    public:
        /**
         * \brief Constructor from an addrinfo struct.
         */
        AddrInfo(::addrinfo* info)
            : info_{info}
        {}

        ~AddrInfo()
        {
            freeaddrinfo(info_);
        }

        AddrInfo(const AddrInfo&) = delete;
        AddrInfo& operator=(const AddrInfo&) = delete;
        AddrInfo(AddrInfo&& addr)
            : info_{std::exchange(addr.info_, nullptr)}
        {}
        AddrInfo& operator=(AddrInfo&& addr)
        {
            freeaddrinfo(info_);
            info_ = std::exchange(addr.info_, nullptr);
            return *this;
        }

        /**
         * \brief Begin of the list of addresses.
         */
        addrinfo_iterator begin()
        {
            return addrinfo_iterator(info_);
        }

        /**
         * \brief Begin of the const list of addresses.
         */
        addrinfo_const_iterator begin() const
        {
            return addrinfo_const_iterator(info_);
        }

        /**
         * \brief End of the list of addresses.
         */
        addrinfo_iterator end()
        {
            return addrinfo_iterator();
        }

        /**
         * \brief End of the const list of addresses.
         */
        addrinfo_const_iterator end() const
        {
            return addrinfo_const_iterator();
        }

    private:
        /**
         * \brief Addrinfo structure held by the object.
         */
        ::addrinfo* info_;
    };

    /**
     * \class AddrInfoHint
     * \brief Builder class used to specify requirements about addresses
     * returned by getaddrinfo(3).
     */
    struct AddrInfoHint : public ::addrinfo
    {
        AddrInfoHint()
        {
            memset(this, 0, sizeof(::addrinfo));
        }

        /**
         * \brief Specify the flag member of the structure.
         */
        AddrInfoHint& flags(int val)
        {
            this->ai_flags = val;
            return *this;
        }

        /**
         * \brief Specify the family member of the structure.
         */
        AddrInfoHint& family(int val)
        {
            this->ai_family = val;
            return *this;
        }

        /**
         * \brief Specify the socktype member of the structure.
         */
        AddrInfoHint& socktype(int val)
        {
            this->ai_socktype = val;
            return *this;
        }

        /**
         * \brief Specify the protocol member of the structure.
         */
        AddrInfoHint& protocol(int val)
        {
            this->ai_protocol = val;
            return *this;
        }

        /**
         * \brief Specify the member of the structure.
         */
        AddrInfoHint& addrlen(socklen_t val)
        {
            this->ai_addrlen = val;
            return *this;
        }

        /**
         * \brief Specify the addr member of the structure.
         */
        AddrInfoHint& addr(::sockaddr* val)
        {
            this->ai_addr = val;
            return *this;
        }

        /**
         * \brief Specify the canonname member of the structure.
         */
        AddrInfoHint& canonname(char* val)
        {
            this->ai_canonname = val;
            return *this;
        }

        /**
         * \brief Specify the member next of the structure.
         */
        AddrInfoHint& next(::addrinfo* val)
        {
            this->ai_next = val;
            return *this;
        }
    };

    /**
     * \brief Wrapper around getaddrinfo(3).
     */
    AddrInfo getaddrinfo(const char* node, const char* service,
                         const AddrInfoHint& hints);
} // namespace misc

/**
 * \brief Outputs the addrinfo to a stream.
 *
 * Only used for debug purposes.
 */
std::ostream& operator<<(std::ostream&, const ::addrinfo&);
