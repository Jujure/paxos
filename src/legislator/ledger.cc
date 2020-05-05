#include "ledger.hh"
#include "legislator.hh"
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


    Vote Ledger::prev_vote()
    {
        Vote v;
        v.legislator = self->config_.name;
        v.ballot_id = read_file(base_path_ + "prev-vote-id.txt");
        Decree decree;
        decree.decree = read_file(base_path_ + "prev-vote-decree.txt");
        v.decree = decree;
        return v;
    }

    void Ledger::set_prev_vote(Vote v)
    {
        write_file(base_path_ + "prev-vote-id.txt", v.ballot_id);
        write_file(base_path_ + "prev-vote-decree.txt", v.decree.decree);
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
