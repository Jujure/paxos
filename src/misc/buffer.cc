#include <iostream>
#include <exception>

#include "error/connection-closed.hh"
#include "misc/buffer.hh"

namespace misc
{
    constexpr size_t CRLF_LENGTH = 2;

    constexpr size_t BUFF_SIZE = 8192;

    Buffer::Buffer()
    {
        data_ = std::deque<std::string>(1);
    }

    void Buffer::append(const std::string& tab)
    {
        size_t crlf_pos = tab.find("\r\n");
        data_.back() += tab.substr(0, crlf_pos);
        size_t line_begin = crlf_pos + CRLF_LENGTH;

        while (crlf_pos != tab.npos && line_begin < tab.size())
        {
            data_.back() += "\r\n";

            crlf_pos = tab.find("\r\n", line_begin);

            data_.emplace_back(tab, line_begin, crlf_pos - line_begin);

            line_begin = crlf_pos + CRLF_LENGTH;
        }

        if (crlf_pos != tab.npos && line_begin == tab.size())
        {
            data_.back() += "\r\n";
            data_.emplace_back();
        }
    }

    size_t Buffer::receive(paxos::Socket& socket)
    {
        char buf[BUFF_SIZE];
        ssize_t n = socket.recv(buf, BUFF_SIZE);
        if (n == 0)
            throw paxos::ConnectionRecvClosedError();
        if (n == -1)
            return 0;

        auto str = std::string(buf, n);

        this->append(str);
        return n;
    }

    std::string Buffer::popline()
    {
        if (this->empty())
            throw std::logic_error("Buffer::popline : pop in a empty Buffer");

        std::string toReturn = data_.front();
        data_.pop_front();
        if (data_.size() == 0)
            data_.emplace_back();

        return toReturn;
    }

    void Buffer::pop_front(size_t content_length)
    {
        while (data_.front().size() < content_length)
        {
            content_length -= data_.front().size();
            data_.pop_front();
        }
        data_.front() = data_.front().substr(content_length);
        if (data_.front().empty() && data_.size() > 1)
            data_.pop_front();
    }

    bool Buffer::empty() const
    {
        return this->get_nb_lines() == 0 && data_.back().empty();
    }

    const std::string& Buffer::getline(size_t line) const
    {
        try
        {
            return data_[line];
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "[Buffer::getline(size_t line)] "
                        << line << "out of " << data_.size();
            exit(1);
        }
    }

    size_t Buffer::get_nb_lines() const
    {
        return data_.size() - 1;
    }

    std::string Buffer::to_string() const
    {
        std::string str;
        for (auto line : data_)
            str += line;
        return str;
    }
}
