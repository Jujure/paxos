/**
 * \file events/register.hh
 * \brief EventWatcherRegistry declaration.
 */

#pragma once

#include <ev.h>
#include <memory>
#include <optional>
#include <unordered_map>

#include "events/event-loop.hh"
#include "events/events.hh"

namespace paxos
{
    /**
     * \class EventWatcherRegistry
     * \brief Registry containing an ev_loop and its ev_io.
     *
     * This class is used to instantiate a global registry inside of each
     * instance of the server. Each registry will contain an EventLoop and
     * its associated EventWatchers.
     * An ev_io stores a raw pointer that needs to be immutable. To ensure
     * that, we allocate EventWatcher using smart pointers. The registry
     * holds a map to translate raw pointer to the smart one.
     */
    class EventWatcherRegistry
    {
    public:
        EventWatcherRegistry() = default;
        EventWatcherRegistry(const EventWatcherRegistry&) = delete;
        EventWatcherRegistry& operator=(const EventWatcherRegistry&) = delete;
        EventWatcherRegistry(EventWatcherRegistry&&) = delete;
        EventWatcherRegistry& operator=(EventWatcherRegistry&&) = delete;

        ~EventWatcherRegistry() = default;

        /**
         * \brief Register a given event watcher.
         *
         * Associate the address stored in the ev_io data with a new
         * EventWatcher instance inside of the registry's events_ map to
         * operate on the ev_io as an EventWatcher object. Then, register this
         * ev_io inside of the loop to start receiving its events.
         *
         * \param args Args variadic number of arguments of unknown types used
         * to construct a specific EventWatcher with the proper parameters.
         * \return A shared pointer on the constructed EventWatcher object.
         */
        template <typename EventWatcher, typename... Args>
        std::shared_ptr<EventWatcher> register_event(Args&&...);

        /**
         * \brief Unregister a given event watcher.
         *
         * \param watcher EventWatcher* to unregister.
         * \return If the operation was successful.
         */
        bool unregister_ew(EventWatcher*);

        /**
         * \brief Access EventWatcher in the map.
         *
         * \param watcher EventWatcher* key to the events_ map.
         * \return The found EventWatcher otherwise std::nullopt.
         */
        std::optional<std::shared_ptr<EventWatcher>> at(EventWatcher*);

        EventLoop& get_event_loop()
        {
            return loop_;
        }

    private:
        /**
         * \brief Map used to store EventWatchers
         *
         * This map is used to associate an ev_io to its registered
         * EventWatcher instance.
         */
        std::unordered_map<EventWatcher*, std::shared_ptr<EventWatcher>>
            events_;

        /**
         * \brief Registry's event loop.
         */
        EventLoop loop_;
    };

    /**
     * \brief Service object.
     */
    extern EventWatcherRegistry event_register;
} // namespace http

#include "events/register.hxx"
