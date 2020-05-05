#pragma once
#include <memory>
#include <string>

#include "events/events.hh"

namespace paxos
{
    class RecvEW : public EventWatcher
    {
     public:
        /**
         * \brief Create a RecvEW from a listener socket.
         */
        explicit RecvEW(shared_socket socket);
        explicit RecvEW(shared_connection connection);
        /**
         * \brief Read on socket.
         */
        void operator()() final;

        shared_connection& get_connection();

    private:
        explicit RecvEW(int socket);

        shared_connection connection_;
    };
}
