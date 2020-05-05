#include "legislator.hh"
#include "misc/logger.hh"
#include <string>

namespace paxos
{
    Legislator::Legislator(const LegislatorConfig& config)
        : config_(config), ledger(config.name)
    {
        log("created legislator " + config.name, blue);
    }

    void Legislator::initiate_ballot()
    {
        int new_ballot_number = ledger.last_tried() + 1;
        ledger.set_last_tried(new_ballot_number);
        log(config_.name + " is initiating ballot " + std::to_string(new_ballot_number), cyan);
        send_next_ballot(new_ballot_number);
    }

    void Legislator::send_next_ballot(int ballot)
    {
        ballot = ballot;
        return;
    }

    void Legislator::receive_next_ballot(int ballot, std::string sender)
    {
        log(config_.name + " has received a NextBallot("
                + std::to_string(ballot)
                + ") from " + sender, cyan);
        int next_ballot = ledger.next_bal();
        if (ballot <= next_ballot)
        {
            log("but it was discarded because ballot " + std::to_string(ballot)
                    + " is inferior or equal to nextBallot "
                    + std::to_string(next_ballot), red);
            return;
        }
        ledger.set_next_bal(ballot);
        int previous_vote = ledger.prev_vote();
        previous_vote = previous_vote;
        //XXX send a LastVote to sender
    }

    void Legislator::receive_enough_last_vote
        (std::unordered_map<std::string, int> quorum_last_votes)
    {
        quorum_last_votes = quorum_last_votes;
        //find d to satisfy B3
        //send BeginBallot to the quorum
    }

    void Legislator::receive_begin_ballot(int ballot, int decree)
    {
        if (ballot != ledger.next_bal())
            return;
        ledger.set_prev_vote(ballot);

        decree = decree;
        //XXX send Voted
    }
}
