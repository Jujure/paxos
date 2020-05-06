/**
 * \file socket/socket.hh
 * \brief Socket declaration.
 */

#pragma once
#include <iostream>

#include <arpa/inet.h>
#include <cstring>
#include <memory>
#include <string>
#include <sys/socket.h>

#include "misc/fd.hh"
#include "misc/socket.hh"

namespace paxos
{
    /**
     * \struct Socket
     * \brief Value object representing a socket.
     *
     * socket(7)
     */
    struct Socket
    {
        /**
         * \brief Create a Socket from a fd.
         */
        explicit Socket(const misc::shared_fd& fd)
            : fd_{fd}
        {}

        Socket() = default;
        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;
        Socket(Socket&&) = default;
        Socket& operator=(Socket&&) = default;
        virtual ~Socket() = default;

        /**
         * \brief recv(2).
         */
        virtual ssize_t recv(void* dst, size_t len) = 0;

        /**
         * \brief send(2).
         */
        virtual ssize_t send(const void* src, size_t len) = 0;

        /**
         * \brief sendfile(2).
         */
        virtual ssize_t sendfile(misc::shared_fd&, off_t&, size_t) = 0;

        /**
         * \brief bind(2).
         */
        virtual void bind(const sockaddr* addr, socklen_t addrlen) = 0;

        /**
         * \brief listen(2).
         */
        virtual void listen(int backlog) = 0;

        /**
         * \brief fcntl(2). Demander aux yaka
         */
        virtual void fcntl_set_O_NONBLOCK() = 0;

        /**
         * \brief setsockopt(2).
         */
        virtual void setsockopt(int level, int optname, int optval) = 0;

        /**
         * \brief getsockopt(2).
         */
        virtual void getsockopt(int level, int optname, int& optval) = 0;

        /**
         * \brief accept(2).
         */
        virtual std::shared_ptr<Socket> accept(sockaddr* addr,
                                               socklen_t* addrlen) = 0;


        std::string getsockname() const
        {
            char ip[INET6_ADDRSTRLEN];
            struct sockaddr_in6 addr;
            bzero(&addr, sizeof(struct sockaddr_in6));
            unsigned int len = sizeof(struct sockaddr_in6);
            sys::getsockname(fd_->fd_, (struct sockaddr *) &addr, &len);
            if (addr.sin6_family == AF_INET6)
                inet_ntop(addr.sin6_family, &addr.sin6_addr, ip,
                        INET6_ADDRSTRLEN);
            else
                inet_ntop(addr.sin6_family,
                        &((struct sockaddr_in *)&addr)->sin_addr, ip,
                        INET6_ADDRSTRLEN);
            return ip;
        }

        std::string getpeername()
        {
            char ip[INET6_ADDRSTRLEN];
            struct sockaddr_in6 addr;
            bzero(&addr, sizeof(struct sockaddr_in6));
            unsigned int len = sizeof(struct sockaddr_in6);
            sys::getpeername(fd_->fd_, (struct sockaddr *) &addr, &len);
            if (addr.sin6_family == AF_INET6)
                inet_ntop(addr.sin6_family, &addr.sin6_addr, ip,
                        INET6_ADDRSTRLEN);
            else
                inet_ntop(addr.sin6_family,
                        &((struct sockaddr_in *)&addr)->sin_addr, ip,
                        INET6_ADDRSTRLEN);
            return ip;
         }



        /**
         * \brief connect(2).
         */
        virtual void connect(const sockaddr*, socklen_t) = 0;

        const misc::shared_fd fd_get() const noexcept
        {
            return fd_;
        }


        const std::string& get_port() const
        {
            return port_;
        }

        void set_port(const std::string& port)
        {
            port_ = port;
        }

        const std::string& get_listener_port() const
        {
            return listener_port_;
        }

        void set_listener_port(const std::string& listener_port)
        {
            listener_port_ = listener_port;
        }

        const std::string& get_ip() const
        {
            return ip_;
        }

        void set_ip(const std::string& ip)
        {
            ip_ = ip;
        }

    protected:
        /**
         * \brief File descriptor of the socket.
         */
        misc::shared_fd fd_;

        /**
         * \brief The port of the socket
         */
        std::string port_;

        /**
         * \brief The port of the listening socket which accepted this socket
         */
        std::string listener_port_;

        /**
         * \brief The ip of the socket
         */
        std::string ip_;
    };

    using shared_socket = std::shared_ptr<Socket>;
} // namespace paxos
