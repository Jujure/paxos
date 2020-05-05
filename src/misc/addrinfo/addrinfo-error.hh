/**
 * \file misc/addrinfo/addrinfo-error.hh
 * \brief Implementation of an extention to system_errors for addrinfo.
 */
#pragma once

#include <boost/iterator/iterator_facade.hpp>
#include <netdb.h>
#include <system_error>

namespace misc
{
    /**
     * \enum addrinfo_error
     * \brief Possible errors returned by getaddrinfo.
     */
    enum addrinfo_error
    {
        BADFLAGS = EAI_BADFLAGS,
        NONAME = EAI_NONAME,
        AGAIN = EAI_AGAIN,
        FAIL = EAI_FAIL,
        FAMILY = EAI_FAMILY,
        SOCKTYPE = EAI_SOCKTYPE,
        SERVICE = EAI_SERVICE,
        MEMORY = EAI_MEMORY,
        SYSTEM = EAI_SYSTEM,
        OVERFLOW = EAI_OVERFLOW,
        NODATA = EAI_NODATA,
        ADDRFAMILY = EAI_ADDRFAMILY,
        INPROGRESS = EAI_INPROGRESS,
        CANCELED = EAI_CANCELED,
        NOTCANCELED = EAI_NOTCANCELED,
        ALLDONE = EAI_ALLDONE,
        INTR = EAI_INTR,
        IDN_ENCODE = EAI_IDN_ENCODE,
    };

    /**
     * \class addrinfo_error_category
     * \brief Error category signifying the system error coming from
     * getaddrinfo.
     */
    class addrinfo_error_category : public std::error_category
    {
    public:
        /**
         * \brief Name of the category.
         */
        virtual const char* name() const noexcept override
        {
            return "addrinfo_error_category";
        }
        /**
         * \brief Error message.
         */
        virtual std::string message(int value) const override
        {
            return gai_strerror(value);
        }
    };

    /**
     * \brief Singleton instance of the new error_category.
     */
    const std::error_category& addrinfo_category();
} // namespace misc

namespace std
{
    /**
     * \brief Setup addrinfo_error to be used as error_codes.
     */
    template <>
    struct is_error_code_enum<misc::addrinfo_error> : public std::true_type
    {};

    /**
     * \brief Translation between addrinfo_errors and error_codes.
     */
    inline std::error_code make_error_code(misc::addrinfo_error e);
} // namespace std
