#pragma once

#include <string>
#include "misc/json.hh"

namespace paxos
{
    [[noreturn]] void error_and_exit(int code, const std::string& error);

} // namespace paxos

#include "parse.hxx"
