/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "Event.h"

using namespace gui;


Event::Event() :
    type(EventType::NONE),
    obj(NULL)
{
}

Event::Event(EventType eventType, EventObject *obj) :
    type(eventType),
    obj(obj)
{
}

Event::Event(Event&& other)
{
    type = other.type;
    obj = other.obj;

    other.obj = NULL;
    other.type = EventType::NONE;
}

Event& Event::operator=(Event&& other)
{
    type = other.type;
    obj = other.obj;

    other.obj = NULL;
    other.type = EventType::NONE;

    return *this;
}

Event::~Event()
{
    if(obj != NULL)
        delete obj;
}
