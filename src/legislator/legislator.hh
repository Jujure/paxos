#pragma once
#include "config/config.hh"
#include "ledger.hh"
#include "message/message.hh"
#include "vote.hh"
#include "law/decree.hh"
#include <unordered_map>
#include <unordered_set>

namespace paxos
{
    class Legislator
    {
    public:
        Legislator(const LegislatorConfig& config);
        LegislatorConfig config_;

        void initiate_ballot();
        int get_next_ballot_id();

        void send_next_ballot(int ballot);
        void receive_next_ballot(Message message);
        void receive_next_ballot(int ballot, std::string sender);

        void send_last_vote(int ballot, Vote previous_vote, std::string sender);
        void receive_last_vote(Message message);
        void receive_enough_last_vote();

        void send_begin_ballot(int ballot, Decree decree);
        void receive_begin_ballot(Message message);
        void receive_begin_ballot(int ballot, int decree, std::string sender);

        void send_voted(int ballot, Decree decree, std::string receiver);
        void receive_voted(Message message);
        void receive_voted(int ballot, Decree decree, std::string voter);
        void receive_enough_voted(int ballot, Decree decree);

        void send_success(Decree decree);
        void receive_success(Message message);
        void receive_success(Decree decree);

        void handle_message(Message message);

    private:
        Ledger ledger;
        std::unordered_map<std::string, Vote> quorum_previous_votes;
        bool has_started;

    };
    using shared_legislator = std::shared_ptr<Legislator>;

    extern shared_legislator self;
    extern std::unordered_map<std::string, shared_legislator> legislators;
}
