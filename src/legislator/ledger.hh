#pragma once
#include <string>
#include <vector>

#include "law/decree.hh"

namespace paxos
{
    class Ledger
    {
    public:
        Ledger(std::string path);

        std::vector<Decree> get_decrees();

        int last_tried();
        void set_last_tried(int b);

        int prev_vote();
        void set_prev_vote(int v);

        int next_bal();
        void set_next_bal(int b);

    private:
        std::string base_path_;

        int read_file(std::string path);
        void write_file(std::string path, int n);
    };
}
