/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <functional>

#include "Event.h"

namespace gui
{

//! Wrapper for std::function; used by EventEmitter to append IDs to listening functions.

class EventListener
{
    public:
        typedef std::function<void(Event&)> Function;
        typedef unsigned int Id;

        EventListener() {};
        EventListener(Function function);

        void bind(Function& function);
        void operator() (Event& event);

    protected:

    private:
        Function func;
        EventListener::Id id;

    friend class EventEmitter;
    friend class GUISystem;
};

}

#endif // EVENTLISTENER_H
