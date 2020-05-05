#include "events/events.hh"

#include "events/register.hh"

namespace paxos
{
    EventWatcher::EventWatcher(int fd, int flags)
    {
        ev_io_init(&watcher_, EventWatcher::event_callback, fd, flags);
        watcher_.data = reinterpret_cast<void*>(this);
    }


    void EventWatcher::event_callback(struct ev_loop*, ev_io* w, int)
    {
        auto ew = reinterpret_cast<EventWatcher*>(w->data);
        auto shared_ew = event_register.at(ew).value();
        (*shared_ew)();
    }
} // namespace http
