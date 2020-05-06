#pragma once

#include <iostream>
#include "parse.hh"

namespace paxos
{
    template <typename ValueType>
    bool safe_get_key(const json& json_obj, const std::string& key,
            ValueType& value, bool mandatory = false)
    {
        try
        {
            json_obj.at(key).get_to(value);
        }
        catch (json::out_of_range& e)
        {
            if (mandatory)
               error_and_exit(1, "parse_configuration: mandatory key '"
                        + key + "' not found.");
            return 0;
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << " in " << key << "\n";
            error_and_exit(1, "parse_configuration: key '" + key +
                    "' is associated with a value of bad type");
        }
        return 1;
    }

} // namespace paxos
