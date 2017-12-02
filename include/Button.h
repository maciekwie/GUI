/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "Renderer.h"
#include "Widget.h"

namespace gui
{

class GUISystem;

//! Button widget. That rectangular thing with inscription on it.

class Button : public Widget
{
    public:
        Button(GUISystem *guiSystem, int x, int y, int w, int h, std::string text);
        virtual ~Button() {};

        virtual void render(Renderer *renderer);
        void stateChange(Widget::State state);
        void setText(const std::string &text);

        Color upStateColor;
        Color hoverStateColor;
        Color downStateColor;
        Color textColor;

    protected:

    private:
        std::string text;
};

}

#endif // BUTTON_H
