#include <cerrno>

#include "socket/default-socket.hh"
#include "misc/socket.hh"
#include "misc/unistd.hh"
#include "error/connection-closed.hh"

#include <iostream>

namespace paxos
{
    DefaultSocket::DefaultSocket(const misc::shared_fd& fd)
        : Socket(fd)
    {}

    DefaultSocket::DefaultSocket(int domain, int type, int protocol)
        : Socket{std::make_shared<misc::FileDescriptor>(
                sys::socket(domain, type, protocol))}
    {
    }

    void DefaultSocket::listen(int backlog)
    {
        sys::listen(*fd_, backlog);
    }

    ssize_t DefaultSocket::recv(void* dst, size_t len)
    {
        return sys::recv(*fd_, dst, len, MSG_NOSIGNAL);
    }

    ssize_t DefaultSocket::send(const void* src, size_t len)
    {
        return sys::send(*fd_, src, len, MSG_NOSIGNAL);
    }

    ssize_t DefaultSocket::sendfile(misc::shared_fd& fd, off_t& offset, size_t len)
    {
        return sys::sendfile(*fd_, *fd, &offset, len);
    }

    void DefaultSocket::bind(const sockaddr* addr, socklen_t addrlen)
    {
        sys::bind(*fd_, addr, addrlen);
    }

    void DefaultSocket::fcntl_set_O_NONBLOCK()
    {
        fd_->fcntl_set(O_NONBLOCK);
    }

    void DefaultSocket::setsockopt(int level, int optname, int optval)
    {
        sys::setsockopt(*fd_, level, optname, &optval, sizeof(int));
    }

    void DefaultSocket::getsockopt(int level, int optname, int& optval)
    {
        unsigned int optlen;
        sys::getsockopt(*fd_, level, optname, &optval, &optlen);
    }

    shared_socket DefaultSocket::accept(sockaddr* addr, socklen_t* addrlen)
    {
        misc::shared_fd client_fd = std::make_shared<misc::FileDescriptor>(sys::accept(*fd_, addr, addrlen));

        auto ret = std::make_shared<DefaultSocket>(client_fd);

        //Set the ip and listener_port of the accepted socket
        ret->set_listener_port(port_);
        ret->set_ip(ip_);
        return ret;
    }

    void DefaultSocket::connect(const sockaddr* addr, socklen_t len)
    {
        sys::connect(*fd_, addr, len);
    }

    // Implement all other methods (see header).
} // namespace paxos
