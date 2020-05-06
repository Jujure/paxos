#include "logger.hh"

#include <iostream>

namespace paxos
{
    void log(std::string str, Color color)
    {
        std::cout << "\033[1;" + std::to_string(color) + "m" + str + "\033[0m\n";
    }
} // namespace paxos
