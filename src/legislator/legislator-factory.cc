#include <memory>

#include "legislator-factory.hh"

namespace paxos
{
    shared_legislator LegislatorFactory::Create(LegislatorConfig& config)
    {
        auto shared = std::make_shared<Legislator>(config);
        return shared;
    }
}
