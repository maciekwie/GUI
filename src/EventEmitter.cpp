/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "EventEmitter.h"

#include <algorithm>
#include <utility>

#include "GUISystem.h"
#include "loggerLocator.h"

using namespace gui;

EventEmitter::EventEmitter() :
    lastListenerId(0)
{
}

EventEmitter::~EventEmitter()
{
}

void EventEmitter::setQueue(AddToQueue addFunction)
{
    addToQueue = addFunction;
}

EventListener::Id EventEmitter::addEventListener(EventType eventType, EventListener::Function listenerFunc)
{
    EventListener listener(listenerFunc);
    listener.id = ++lastListenerId;
    eventListeners.emplace(eventType, listener);

    return listener.id;
}

void EventEmitter::removeEventListener(EventListener::Id listenerId)
{
    auto iter = std::find_if(eventListeners.begin(), eventListeners.end(), MapPredicate(listenerId));

    eventListeners.erase(iter);
}

void EventEmitter::emitEvent(Event& event)
{
    auto range = eventListeners.equal_range(event.getType());

    for(Map::iterator i = range.first; i != range.second; i++)
    {
        Event evtCopy = guiSystem->cloneEvent(event);
        addToQueue(evtCopy, i->second);
    }
}
