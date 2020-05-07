#include "events/send.hh"
#include "events/receive.hh"
#include "events/register.hh"
#include "error/connection-closed.hh"
#include "error/parsing-error.hh"
#include "misc/logger.hh"
#include "misc/addrinfo/addrinfo.hh"
#include "error/connection-failed.hh"

namespace paxos
{
    SendEW::SendEW(shared_connection connection)
        : EventWatcher(connection->get_socket_fd()->fd_, EV_WRITE)
        , connection_(connection)
    {
    }

    SendEW::~SendEW()
    {
    }

    void SendEW::operator()()
    {
        shared_socket sock = connection_->get_socket();

        auto buffer = connection_->get_buffer_out();
        std::string response = buffer.to_string();
        log("Sending a message: ", blue);

        log(response, white);
        ssize_t write = 0;
        try
        {
            write = sock->send(response.c_str(), response.size());
        }
        catch (const std::system_error& e)
        {
            std::cerr << "Connection closed while sending\n";
            event_register.unregister_ew(this);
            return;
        }

        if (write == -1)
            return;

        buffer.pop_front(write);
        if (!buffer.empty())
            return;

        event_register.unregister_ew(this);
    }
}
