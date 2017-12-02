/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <functional>
#include <string>
#include <forward_list>

#include "Renderer.h"
#include "EventEmitter.h"
#include "Event.h"

namespace gui
{

class Event;

//! Base class for widgets. Inherits EventEmitter.

class Widget : public EventEmitter
{
    public:
        typedef char State;
        enum states { STATE_HOVER, STATE_DOWN, STATE_UP };

        Widget();
        Widget(int x, int y, int w, int h);
        virtual ~Widget();

        virtual void render(Renderer *renderer);
        virtual void keyChar(int uchar);
        virtual void keyDown(int keyCode);
        virtual void mouseMove(int x, int y);
        virtual void stateChange(State state);
        virtual void focusIn();
        virtual void focusOut();

        void addChild(Widget *widget);
        void removeChild(Widget *widget);
        void setParent(Widget *widget);
        void resize(int x, int y, int w, int h);
        void updateAbs();

        void setVisibility(bool visible);

        bool contain(int posX, int posY);
        bool isFocused() { return focused; };
        State getState() { return state; };

    protected:
        int x, y, w, h;
        int xAbs, yAbs;
        int state;
        bool focused;
        bool visible;

    private:
        Widget *parent;
        std::forward_list<Widget*> children;

    friend class GUISystem;
};

}

#endif // WIDGET_H
