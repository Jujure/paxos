#include <optional>
#include <string>
#include <sstream>

#include "error/parsing-error.hh"
#include "message.hh"
#include "misc/addrinfo/addrinfo.hh"
#include "error/connection-failed.hh"
#include "events/send.hh"
#include "misc/logger.hh"
#include "events/register.hh"


namespace paxos
{
    static inline bool is_white_space(char c)
    {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    static inline bool is_digit(const char c)
    {
        return c >= '0' && c <= '9';
    }

    static inline bool is_t_char(char c)
    {
        return c == '!' || c == '#' || c == '$' || c == '%' || c == '&'
            || c == '\'' || c == '*' || c == '+' || c == '-' || c == '.'
            || c == '^' || c == '_' || c == '`' || c == '|' || c == '~'
            || is_digit(c) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    void strip_white_spaces(std::string& str)
    {
        int nb_leading_white_spaces = 0;
        for (auto i = str.begin(); i != str.end()
                && is_white_space(*i); ++i)
            ++nb_leading_white_spaces;
        str.erase(0, nb_leading_white_spaces);

        auto len = str.size();
        while (len && is_white_space(str[len - 1]))
        {
            str.pop_back();
            len = str.size();
        }
    }

    static inline bool contains_only_tchars(const std::string& str)
    {
        for (auto c : str)
            if (!is_t_char(c))
                return false;
        return true;
    }

    bool Message::parse_first_line(const std::string& line)
    {
        std::istringstream stream(line);
        stream >> method_;
        if (stream.eof())
            return false;
        std::string crlf;
        stream >> crlf;
        return true;
    }

    bool Message::parse_header(const std::string& header_line)
    {
        auto name_separator_index = header_line.find_first_of(':');
        if (name_separator_index == std::string::npos)
            return false;

        auto header_name = header_line.substr(0, name_separator_index);
        if (!contains_only_tchars(header_name))
            throw ParsingError("Forbidden whitespace in header name");

        auto field_value = header_line.substr(name_separator_index + 1);

        strip_white_spaces(field_value);

        return parse_header(header_name, field_value);
    }

    bool Message::parse_header(std::string& header_name,
            const std::string& field_value)
    {
        if (headers_[header_name] == "")
            headers_[header_name] = field_value;
        else
            headers_[header_name] += "," + field_value;
        return true;
    }


    void Message::pop_buffer(misc::Buffer& buffer)
    {
        for (auto line = buffer.popline();
                line != "\r\n";
                line = buffer.popline())
            continue;
    }

    std::string& Message::get_method()
    {
        return method_;
    }

    void Message::set_method(std::string method)
    {
        method_ = method;
    }

    Message::headers_map_t& Message::get_headers()
    {
        return headers_;
    }

    std::optional<std::string> Message::get_header(std::string header_name) const
    {
        auto res = headers_.find(header_name);
        if (res == headers_.end())
            return std::nullopt;

        return res->second;
    }


    void Message::add_header(std::string header,
                                const std::string& header_value)
    {
        headers_[header] = header_value;
    }

    void Message::remove_header(std::string header)
    {
        auto header_iter = headers_.find(header);
        if (header_iter != headers_.end())
            headers_.erase(header_iter);
    }

    void Message::fill_buffer(misc::Buffer& buffer)
    {
        std::string first_line = get_method() + "\r\n";
        buffer.append(first_line);

        std::string headers;
        for (auto header: get_headers())
            headers += header.first + ": " + header.second + "\r\n";

        buffer.append(headers);
        buffer.append("\r\n");
    }

    bool Message::parse(misc::Buffer& buffer)
    {
        if (buffer.empty())
            return false;
        size_t line_nb = 0;
        if (!parse_first_line(buffer.getline(line_nb)))
        {
            if (buffer.get_nb_lines() == 0)
                return false;
            else
                 throw ParsingError("First line too short");
        }
        ++line_nb;
        for (auto line = buffer.getline(line_nb);
                line_nb < buffer.get_nb_lines() && line != "\r\n";
                line = buffer.getline(line_nb))
        {
            if (!parse_header(line))
            {
                if (line_nb == buffer.get_nb_lines())
                    return false;
                else
                    throw ParsingError("Invalid header");
            }
            ++line_nb;
        }
        if (line_nb >= buffer.get_nb_lines())
            return false;

        pop_buffer(buffer);

        return true;
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

    void Message::send(shared_legislator receiver)
    {
        std::string ip = receiver->config_.ip;
        std::string port = receiver->config_.port;
        std::string name = receiver->config_.name;
        add_header("receiver", name);
        shared_socket socket;
        try
        {
            socket = connect_to_ip_port(ip, port);
        }
        catch (const ConnectionFailed& e)
        {
            log("Could not connect to " + name, red);
            return;
        }

        shared_connection connection = std::make_shared<Connection>(socket);
        fill_buffer(connection->get_buffer_out());

        event_register.register_event<SendEW>(connection);
    }

}
