#include "error/parsing-error.hh"
#include "error/connection-closed.hh"
#include "events/receive.hh"
#include "events/register.hh"
#include "events/send.hh"
#include "misc/addrinfo/addrinfo.hh"

namespace paxos
{
    RecvEW::RecvEW(int socket)
        : EventWatcher(socket, EV_READ)
    {
    }

    RecvEW::RecvEW(shared_socket socket)
        : RecvEW(socket->fd_get()->fd_)
    {
        connection_ = std::make_shared<Connection>(socket);
    }

    RecvEW::RecvEW(shared_connection connection)
        : RecvEW(connection->get_socket_fd()->fd_)
    {
        connection_ = connection;
    }


    void RecvEW::operator()()
    {

    }


}
