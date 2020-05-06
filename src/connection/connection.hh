/**
 * \file vhost/connection.hh
 * \brief Connection declaration.
 */

#pragma once

#include <iostream>
#include <memory>

#include "misc/fd.hh"
#include "socket/socket.hh"
#include "misc/buffer.hh"

namespace paxos
{
    /**
     * \struct Connection
     * \brief Value object representing a connection.
     *
     * We need to keep track of the state of each request while it has not
     * been fully processed.
     */
    struct Connection
    {
        friend class APM;

        Connection(shared_socket socket);

        Connection(const Connection& con) = default;
        Connection& operator=(const Connection&) = default;
        Connection(Connection&&) = default;
        Connection& operator=(Connection&&) = default;
        ~Connection();

        /* Add members to store the information relative to the
        ** connection.
        */

        const shared_socket& get_socket();
        const misc::shared_fd get_socket_fd();

        /*
        ** \brief Getter of the input misc::Buffer
        ** \return misc::Buffer
        */
        misc::Buffer& get_buffer_in();

        /*
        ** \brief Getter of the output misc::Buffer
        ** \return misc::Buffer
        */
        misc::Buffer& get_buffer_out();

        /**
         * \brief Returns the ip the client accessed while connecting
         */
        const std::string get_origin_ip() const;

        /**
         * \brief Returns the port the client accessed while connecting
         */
        const std::string& get_origin_port() const;

        const std::string& get_servername() const;
        void set_servername(const std::string& servername);

    private:
        shared_socket socket_;
        std::string servername_;
        misc::Buffer buffer_in_;
        misc::Buffer buffer_out_;
    };

    using shared_connection = std::shared_ptr<Connection>;
} // namespace paxos
