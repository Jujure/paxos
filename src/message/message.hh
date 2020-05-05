#pragma once
#include <unordered_map>

#include "misc/buffer.hh"

namespace paxos
{
    class Message
    {
    public:
        //ALIASES
        using headers_map_t = std::unordered_map<std::string, std::string>;

        Message() = default;
        Message(const Message&) = default;
        Message& operator=(const Message&) = default;
        Message(Message&&) = default;
        Message& operator=(Message&&) = default;
        ~Message() = default;

        //PARSING
        bool parse(misc::Buffer& buffer);

        /**
         ** \brief Parse the given header line
         ** \param header_line the header line to parse
         ** \return false if the line is incomplete, true if it is valid
         ** throw a ParsingError if there is a whitespace between the
         ** header name and the first ':'
         ** this is sufficient request invalidity condition.
         */
        bool parse_header(const std::string& header_line);

        /**
         ** \brief Add the given header name and value in the headers map.
         ** If the header name already exists, the new value is concatenated
         ** to the old one with a separating ','.
         ** \param header_name The name of the header to be added, it is case
         ** insensitive
         ** \param field_value the value of the field, white spaces need to
         ** be stripped
         ** \return true
         */
        bool parse_header(std::string& header_name,
                const std::string& field_value);

        bool parse_first_line(const std::string& line);


        //GETTERS

        std::string& get_method();

        headers_map_t& get_headers();
        std::optional<std::string> get_header(std::string header_name) const;

        void pop_buffer(misc::Buffer& buffer);

        void add_header(std::string header, const std::string& header_value);

        void remove_header(std::string header);

        void set_method(std::string method);

        void fill_buffer(misc::Buffer& buffer);

    protected:
        std::string method_;

        headers_map_t headers_;
    };

    void strip_white_spaces(std::string& str);
}
