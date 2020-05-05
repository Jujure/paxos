#pragma once

#include <memory>

#include "events/events.hh"
#include "connection/connection.hh"

namespace paxos
{
    class SendEW : public EventWatcher
    {
    public:
        /**
         * \brief Create a RecvEW from a listener socket.
         */
        explicit SendEW(shared_connection connection);

        ~SendEW();
        SendEW(const SendEW&) = delete;
        SendEW& operator=(const SendEW&) = delete;

        /**
         * \brief Read on socket.
         */
        void operator()() final;

    private:
        shared_connection connection_;
    };

} // namespace http
