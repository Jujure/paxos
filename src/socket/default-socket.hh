/**
 * \file socket/default_socket.hh
 * \brief DefaultSocket declaration.
 */

#pragma once

#include "misc/socket.hh"
#include "socket/socket.hh"

namespace paxos
{
    /**
     * \struct DefaultSocket
     * \brief Implementation of the Socket interface.
     */
    struct DefaultSocket : public Socket
    {
        explicit DefaultSocket(const misc::shared_fd&);
        DefaultSocket(int domain, int type, int protocol);

        DefaultSocket() = default;
        DefaultSocket(const DefaultSocket&) = delete;
        DefaultSocket& operator=(const DefaultSocket&) = delete;
        DefaultSocket(DefaultSocket&&) = default;
        DefaultSocket& operator=(DefaultSocket&&) = default;
        ~DefaultSocket() = default;

        ssize_t recv(void* dst, size_t len) final;

        ssize_t send(const void* src, size_t len) final;

        ssize_t sendfile(misc::shared_fd& fd, off_t& offset, size_t len) final;

        void bind(const sockaddr* addr, socklen_t addrlen) final;

        void listen(int backlog) final;

        void fcntl_set_O_NONBLOCK() final;

        void setsockopt(int level, int optname, int optval) final;

        void getsockopt(int level, int optname, int& optval) final;

        shared_socket accept(sockaddr* addr, socklen_t* addrlen) final;

        void connect(const sockaddr*, socklen_t) final;
    };
} // namespace paxos
