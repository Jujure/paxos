#include "events/send.hh"
#include "events/receive.hh"
#include "events/register.hh"
#include "error/connection-closed.hh"
#include "error/parsing-error.hh"

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

    }
}
