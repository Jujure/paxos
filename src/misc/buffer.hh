#pragma once

#include <deque>
#include <string>

#include "socket/default-socket.hh"

namespace misc
{
    class Buffer
    {
    public:
        Buffer();

        ~Buffer() = default;
        Buffer(const Buffer&) = default;
        Buffer& operator=(const Buffer&) = default;

        /**
        ** \brief Append parsed tab on CRLF characters in data_.
        ** \param tab The buffer received from Socket::recv() to parse.
        */
        void append(const std::string& tab);

        /**
        ** \brief Call the socket recv method and append to the buffer
        ** \param socket The default socket
        */
        size_t receive(http::Socket& socket);

        /**
        ** \brief Pop the string in front of data_ and returns it.
        */
        std::string popline();

        void pop_front(size_t content_length);

        bool empty() const;

        const std::string& getline(size_t line) const;

        size_t get_nb_lines() const;

        std::string to_string() const;

    private:
        std::deque<std::string> data_;
    };
}
