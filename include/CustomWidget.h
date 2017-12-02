/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include "Event.h"
#include "Button.h"

namespace gui
{

class GUISystem;

}

using namespace gui;

//! Test class for adding own widgets mechanism.

class CustomWidget : public Button
{
    public:
        CustomWidget(GUISystem *guiSystem, int x, int y);

        void onClick(Event& event);

    protected:

    private:
};

#endif // CUSTOMWIDGET_H
