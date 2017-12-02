/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef EDITBOX_H
#define EDITBOX_H

#include <string>

#include "keycodes.h"
#include "Widget.h"
#include "Handle.h"
#include "Scrollbar.h"

namespace gui
{

class GUISystem;

//! EditBox widget. You can type into it.

class EditBox : public Widget
{
    public:
        EditBox(GUISystem *guiSystem, int x, int y, int w, int h);
        virtual ~EditBox() {};

        void render(Renderer *renderer);
        void keyChar(int unichar);
        void keyDown(int keyCode);

        void setMultiline();
        void setText(const std::string &text);
        std::string getText();

    protected:
        Color textColor;
        Color frameColor;
        Color backgroundColor;
        Color cursorColor;

        int backspaceCode;

    private:
        void updateScrollbars();
        void getCursorXY(Renderer *renderer, int& cursorX, int& cursorY);
        void findCursorLine();
        void countLines();

        Handle<Scrollbar> vScrollbar;
        Handle<Scrollbar> hScrollbar;

        std::string text;
        unsigned int cursorPos;
        unsigned int cursorLine;
        int lines;
        float lineHeight;
        bool multiline;
        bool vScroll;
        bool hScroll;

    friend class GUISystem;
};

}
#endif // EDITBOX_H
