#include "events/listener.hh"
#include "events/register.hh"
#include "events/receive.hh"
#include "misc/socket.hh"
#include "misc/logger.hh"

namespace paxos
{
    ListenerEW::ListenerEW(shared_socket socket) :
        EventWatcher(socket->fd_get()->fd_, EV_READ)
    {
        /*struct sockaddr_in addr;
        int addrlen = sizeof(addr);
        sys::getsockname(socket->fd_get()->fd_,  &addr, &addrlen);*/

        sock_  = socket;
        //port_ = addr.sin_port;
    }

    void ListenerEW::operator()()
    {
        /* accept client */

        try
        {
            auto client_socket = sock_->accept(nullptr, nullptr);

            client_socket->fcntl_set_O_NONBLOCK();

            std::cout << "Listener: accepting client ... on " <<  getpid() << "\n";

            /* Register client_socket */
            auto e = event_register.register_event<RecvEW>(client_socket);
        }
        catch (const std::system_error& e)
        {
            std::cerr << "Listener: Could not accept client\n";
            return;
        }
    }
}
