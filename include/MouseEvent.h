/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "EventObject.h"

namespace gui
{

class MouseEvent final : public EventObject
{
    public:
        MouseEvent() {}
        ~MouseEvent() {}

        int mouseX, mouseY;

    protected:

    private:
};

}

#endif // MOUSEEVENT_H
