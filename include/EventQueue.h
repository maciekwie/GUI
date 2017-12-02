/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <functional>
#include <utility>
#include <queue>

#include "Event.h"
#include "EventEmitter.h"
#include "events.h"

namespace gui
{

//! GUISystem's internal event queue; collects fired events and affiliates them with particular event listener.

class EventQueue
{
    public:
        EventQueue() {};
        ~EventQueue() {};

        /** \brief Adds an event to the queue and affiliated event listener.
         *
         * \param event The event
         * \param eventListener EventListener handling the event
         *
         */
        void addToQueue(Event& event, EventListener eventListener);

        /** \brief Is queue empty.
         *
         * \return Returns true if the queue is empty.
         *
         */
        bool empty();

        /** \brief Pops an event from the queue. The returned event is removed from the queue.
         *
         * \param eventListener Reference to EventListener handling the event.
         * \return Event
         *
         */
        Event getNextEvent(EventListener &eventListener);

    protected:

    private:
        std::queue<std::pair<Event, EventListener>> queue;
};

}

#endif // EVENTQUEUE_H
