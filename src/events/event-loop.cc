#include "event-loop.hh"

namespace paxos
{
    EventLoop::EventLoop()
    {
        /* Macro equivalent of ev_default_loop(int flags) */
        loop = EV_DEFAULT;
    }

    EventLoop::EventLoop(struct ev_loop* loopev)
    {
        loop = loopev;
    }

    EventLoop::~EventLoop()
    {
        /* Maybe need to stop all watcher or easier, free them */
        ev_loop_destroy(loop);
    }

    void EventLoop::register_watcher(EventWatcher* watcher)
    {
        ev_io_start(loop, &(watcher->watcher_get()));
    }

    void EventLoop::unregister_watcher(EventWatcher* watcher)
    {
        ev_io_stop(loop, &(watcher->watcher_get()));
    }

    void EventLoop::register_sigint_watcher(ev_signal* signal) const
    {
        ev_signal_start(loop, signal);
    }

    void EventLoop::register_timer_watcher(ev_timer* et) const
    {
        ev_timer_start(loop, et);
    }

    void EventLoop::unregister_timer_watcher(ev_timer* et) const
    {
        ev_timer_stop(loop, et);
    }

    void EventLoop::operator()() const
    {
        ev_run(loop, 0);
    }

}
