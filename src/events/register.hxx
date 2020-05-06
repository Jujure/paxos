#pragma once

#include "events/register.hh"

namespace paxos
{
    template <typename EventWatcher, typename... Args>
    std::shared_ptr<EventWatcher>
    EventWatcherRegistry::register_event(Args&&... args)
    {
        auto ew = std::make_shared<EventWatcher>(std::forward<Args>(args)...);

        events_[ew.get()] = ew;
        loop_.register_watcher(ew.get());

        return ew;
    }
} // namespace paxos
