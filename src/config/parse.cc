#include "parse.hh"

namespace paxos
{
    void error_and_exit(int code, const std::string& error)
    {
        /* Display 'error' on stderr and exit with 'code' */
        std::cerr << error << "\n";
        exit(code);
    }

} // namespace paxos
