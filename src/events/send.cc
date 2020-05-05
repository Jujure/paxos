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

    }

    static shared_socket connect_to_ip_port(std::string ip, std::string port)
    {
        /* prepare hints structure */
        misc::AddrInfoHint hints;
        hints.family(AF_UNSPEC);
        hints.socktype(SOCK_STREAM);
        misc::AddrInfo result = misc::getaddrinfo(ip.c_str(), port.c_str(), hints);

        for (auto it : result)
        {
            try
            {
                auto vhost_socket = std::make_shared<DefaultSocket>
                    (it.ai_family, it.ai_socktype, it.ai_protocol);
                vhost_socket->connect(it.ai_addr, it.ai_addrlen);
                vhost_socket->fcntl_set_O_NONBLOCK();
                return vhost_socket;
            }
            catch (const std::exception& e)
            {
                continue;
            }
        }
        throw ConnectionFailed();
    }


    void SendEW::send_message(Message message, shared_legislator legislator)
    {
        std::string ip = legislator->config_.ip;
        std::string port = legislator->config_.port;
        shared_socket socket;
        try
        {
            socket = connect_to_ip_port(ip, port);
        }
        catch (const ConnectionFailed& e)
        {
            log("Could not connect to " + legislator->config_.name, red);
        }

        shared_connection connection = std::make_shared<Connection>(socket);
        message.fill_buffer(connection->get_buffer_out());

        event_register.register_event<SendEW>(connection);
    }
}
