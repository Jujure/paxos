#include <memory>

#include "legislator-factory.hh"
#include "socket/default-socket.hh"
#include "misc/addrinfo/addrinfo.hh"
#include "events/register.hh"
#include "events/listener.hh"

namespace paxos
{
    static shared_socket create_and_bind_socket(const misc::AddrInfo& info)
    {
        int optval = 1;
        for (auto it : info)
        {
        // try to create socket
            try
            {
                /* Create socket */
                shared_socket socket;
                socket = std::make_shared<DefaultSocket>
                    (it.ai_family, it.ai_socktype, it.ai_protocol);

                /* Set socket parameter and bind it */
                socket->setsockopt(SOL_SOCKET,
                        SO_REUSEPORT | SO_REUSEADDR, optval);
                socket->bind(it.ai_addr, it.ai_addrlen);
                socket->fcntl_set_O_NONBLOCK();

                return socket;
            }
            catch (const std::exception& e)
            {
                continue;
            }

        }
        exit(1);
    }

    static shared_socket prepare_socket(LegislatorConfig& conf)
    {
        const std::string& ip = conf.ip;
        const std::string& port = conf.port;
        // prepare hints structure
        misc::AddrInfoHint hints;
        hints.family(AF_UNSPEC);
        hints.socktype(SOCK_STREAM);

        misc::AddrInfo info = misc::getaddrinfo(ip.c_str(), port.c_str(),
                hints);

        // create server socket and listen
        auto legislator_socket = create_and_bind_socket(info);

        //Set ip and port attributes of the listening socket
        legislator_socket->set_port(port);
        legislator_socket->set_ip(ip);

        legislator_socket->listen(SOMAXCONN);

        return legislator_socket;
    }


    shared_legislator LegislatorFactory::Create(LegislatorConfig& config)
    {
        auto shared = std::make_shared<Legislator>(config);
        if (config.is_self)
        {
            shared_socket socket = prepare_socket(config);
            event_register.register_event<ListenerEW>(socket);
        }
        return shared;
    }
}
