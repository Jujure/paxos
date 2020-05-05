/**
 * \file misc/sys-wrapper.hh
 * \brief SysWrapper declaration.
 */

#pragma once

#include <functional>
#include <system_error>
#include <utility>

namespace sys
{
    /**
     * \class SysWrapper
     * \brief Wrapping around syscalls to convert failure into exceptions.
     *
     * Wrapping syscalls this way helps to insure the RAII idiom.
     */
    template <typename RetType, typename SysRetType, typename... Args>
    class SysWrapper
    {
    public:
        SysWrapper(SysRetType syscall(Args...))
            : syscall_{syscall}
        {}

        /* Needs template to enable universal referencing.
           Template deduction should be done automatically. */
        template <typename... UniversalArgs>
        RetType operator()(UniversalArgs&&... args)
        {
            SysRetType ret;

            do
            {
                errno = 0;
                ret = syscall_(std::forward<UniversalArgs>(args)...);
            } while (errno == EINTR);

            if (ret == SysRetType(-1) && errno != EWOULDBLOCK
                && errno != EAGAIN)
            {
                throw std::system_error(errno, std::system_category());
            }

            return RetType(ret);
        }

    private:
        std::function<SysRetType(Args...)> syscall_;
    };

    /**
     * \brief Helper function to build SysWrapper.
     */
    template <typename RetType, typename SysRetType, typename... Args>
    SysWrapper<RetType, SysRetType, Args...>
    make_wrapper(SysRetType syscall(Args...))
    {
        return SysWrapper<RetType, SysRetType, Args...>(syscall);
    }
} // namespace sys
