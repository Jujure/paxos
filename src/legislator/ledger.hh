#pragma once
#include <string>
#include <vector>

#include "law/decree.hh"
#include "vote.hh"

namespace paxos
{
    class Ledger
    {
    public:
        Ledger(std::string path);

        Decree get_decree();
        void set_decree(Decree decree);

        int last_tried();
        void set_last_tried(int b);

        Vote prev_vote();
        void set_prev_vote(Vote v);

        int next_bal();
        void set_next_bal(int b);

    private:
        std::string base_path_;

        int read_file(std::string path);
        void write_file(std::string path, int n);
    };
}
