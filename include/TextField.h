/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <string>

#include "Renderer.h"
#include "Widget.h"

namespace gui
{

class GUISystem;

//! TextField widget. It's like EditBox but no editing.

class TextField : public Widget
{
    public:
        TextField(GUISystem *guiSystem, int x, int y, int w, int h, std::string text);
        virtual ~TextField() {};

        void render(Renderer *renderer);
        void setText(const std::string &text);
        std::string getText();

    protected:
        Color textColor;

    private:
        std::string text;

    friend class GUISystem;
};

}

#endif // TEXTFIELD_H
