#include "connection.hh"

namespace paxos
{
    Connection::Connection(shared_socket socket)
    {
        this->socket_ = socket;
        servername_ = std::string();
    }

    Connection::~Connection()
    {
    }

    const shared_socket& Connection::get_socket()
    {
        return socket_;
    }

    const misc::shared_fd Connection::get_socket_fd()
    {
        return socket_->fd_get();
    }

    misc::Buffer& Connection::get_buffer_in()
    {
        return buffer_in_;
    }

    misc::Buffer& Connection::get_buffer_out()
    {
        return buffer_out_;
    }

    const std::string Connection::get_origin_ip() const
    {
        return socket_->getsockname();
    }

    const std::string& Connection::get_origin_port() const
    {
        return socket_->get_listener_port();
    }

    void Connection::set_servername(const std::string& servername)
    {
        servername_ = servername;
    }

    const std::string& Connection::get_servername() const
    {
        return servername_;
    }
}
