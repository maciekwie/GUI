/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

/** \file events.h
 *  Contains event types labels.
 */

#ifndef EVENTS_H
#define EVENTS_H

#include <functional>

namespace gui
{

enum class EventType : char {
    NONE = 0,
    MOUSE_BUTTON_DOWN,
    MOUSE_BUTTON_UP,
    MOUSE_MOVE,
    KEY_DOWN,
    KEY_UP,
    KEY_PRESS,
    RESIZE,
    DISPLAY_CLOSE,
    USER_EVENT
};

}

#endif // EVENTS_H
