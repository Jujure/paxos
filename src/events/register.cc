#include "register.hh"

namespace paxos
{
    std::optional<std::shared_ptr<EventWatcher>> 
        EventWatcherRegistry::at(EventWatcher* event)
    {
        return events_[event];
    }

    bool EventWatcherRegistry::unregister_ew(EventWatcher *ew)
    {
        if (events_.find(ew) == events_.end())
            return false;

        loop_.unregister_watcher(ew);
        events_.erase(ew);
        return true;
    }
}
