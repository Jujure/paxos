#include "ledger.hh"
#include <fstream>
#include <filesystem>

namespace paxos
{
    Ledger::Ledger(std::string path)
        : base_path_(path)
    {
        std::filesystem::create_directory(path);
        base_path_ += "/";
    }

    std::vector<Decree> Ledger::get_decrees()
    {
        return std::vector<Decree>();
    }

    int Ledger::last_tried()
    {
        return read_file(base_path_ + "last-tried.txt");
    }

    void Ledger::set_last_tried(int b)
    {
        write_file(base_path_ + "last-tried.txt", b);
    }


    int Ledger::prev_vote()
    {
        return read_file(base_path_ + "prev-vote.txt");
    }

    void Ledger::set_prev_vote(int v)
    {
        write_file(base_path_ + "prev-vote.txt", v);
    }

    int Ledger::next_bal()
    {
        return read_file(base_path_ + "next-bal.txt");
    }

    void Ledger::set_next_bal(int b)
    {
        write_file(base_path_ + "next-bal.txt", b);
    }

    int Ledger::read_file(std::string path)
    {
        std::ifstream stream(path);
        if (!stream.good())
            return -1;
        int res;
        stream >> res;
        return res;
    }

    void Ledger::write_file(std::string path, int n)
    {
        std::ofstream stream(path);
        stream << n;
    }
}
