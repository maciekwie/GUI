/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "EventQueue.h"

#include <utility>

using namespace gui;

void EventQueue::addToQueue(Event& event, EventListener eventListener)
{
    queue.push(std::pair<Event, EventListener>(std::move(event), eventListener));
}

bool EventQueue::empty()
{
    return queue.empty();
}

Event EventQueue::getNextEvent(EventListener &eventListener)
{
    std::pair<Event, EventListener> entry = std::move(queue.front());
    Event event = std::move(entry.first);

    queue.pop();

    eventListener = entry.second;

    return event;
}
