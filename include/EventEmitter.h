/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef EVENTEMITTER_H
#define EVENTEMITTER_H

#include <string>
#include <functional>
#include <map>

#include "Event.h"
#include "EventListener.h"
#include "events.h"

namespace gui
{

class GUISystem;

typedef std::function<void(Event&, EventListener)> AddToQueue;

//! Base class for things that emits events.

class EventEmitter
{
    public:
        typedef std::multimap<EventType, EventListener> Map;

        EventEmitter();
        virtual ~EventEmitter();

        /** \brief Assigns addToQueue function so the events can be sent to the queue.
         *
         * \param addFunction Function wrapper of type AddToQueue.
         *
         */
        void setQueue(AddToQueue addFunction);

        /** \brief Adds an event listener.
         *
         * \param eventType The type of event the listener is listening on.
         * \param listenerFunc Function wrapper of type EventListener::Function.
         * \return Listener's identifier assigned by the event emitter.
         */
        EventListener::Id addEventListener(EventType eventType, EventListener::Function listenerFunc);

        /** \brief Removes an event listener.
         *
         * \param listenerId Listener's identifier returned by addEventListener function.
         */
        void removeEventListener(EventListener::Id listenerId);

        /** \brief Emits an event.
         *
         * \param event Event object created by GUISystem.
         */
        void emitEvent(Event& event);

    protected:
        GUISystem *guiSystem;

    private:
        struct MapPredicate : public std::unary_function<EventListener, bool>
        {
            MapPredicate(EventListener::Id id) : id(id) {}

            bool operator() (Map::value_type value)
            {
                return value.second.id == id;
            }

            EventListener::Id id;
        };

        Map eventListeners;
        AddToQueue addToQueue;
        int lastListenerId;

    friend class EventQueue;
};

}

#endif // EVENTEMITTER_H
