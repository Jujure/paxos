#include "error/parsing-error.hh"
#include "error/connection-closed.hh"
#include "events/receive.hh"
#include "events/register.hh"
#include "events/send.hh"
#include "misc/addrinfo/addrinfo.hh"
#include "legislator/legislator.hh"
#include "misc/logger.hh"

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
        shared_socket sock = connection_->get_socket();

        auto origin_ip = connection_->get_origin_ip();
        auto origin_port = connection_->get_origin_port();

        auto buf_in = connection_->get_buffer_in();
        /* Add try catch to handle session */
        try
        {
            buf_in.receive(*sock);
        }
        catch (const std::system_error& e)
        {
            log("Connection closed while receiving on " + origin_ip + ":"
                    + origin_port, red);

            event_register.unregister_ew(this);
            return;
        }

        Message message;
        try
        {
            if (!message.parse(buf_in))
                return;
            self->handle_message(message);
        }
        catch (const std::exception& e)
        {
            log("Bad message", red);
        }

        event_register.unregister_ew(this);

    }


}
