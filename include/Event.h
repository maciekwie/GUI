/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef EVENT_H
#define EVENT_H

#include "events.h"
#include "EventObject.h"

namespace gui
{

class EventObject;

//! Class for objects representing events. Its creation and copying is managed by GUISystem class.

class Event final
{
    public:
        Event(Event&& other);
        Event& operator=(Event&& other);
        ~Event();

        template<class T> T* getEventObject()
        {
            return static_cast<T*>(obj);
        }
        inline EventType getType() {  return type; }

    protected:

    private:
        Event();
        Event(EventType eventType, EventObject *obj);

        //Event(const Event&) = delete;

        /** \brief
         *  One of registered event types.
         */
        EventType type;

        /** \brief
         *  Contains event properties depending on event type.
         */
        EventObject *obj;

    friend class GUISystem;
};

}

#endif // EVENT_H
