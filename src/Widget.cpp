/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "Widget.h"

#include "GUISystem.h"

#include "loggerLocator.h"

using namespace gui;

Widget::Widget() :
    x(0),
    y(0),
    w(0),
    h(0),
    state(STATE_UP),
    focused(false),
    visible(true),
    parent(NULL)
{
    updateAbs();
}

Widget::Widget(int x, int y, int w, int h) :
    x(x),
    y(y),
    w(w),
    h(h),
    state(STATE_UP),
    focused(false),
    visible(true),
    parent(NULL)
{
    updateAbs();
}

Widget::~Widget()
{
    //dtor
}

void Widget::render(Renderer *renderer)
{
}

void Widget::keyChar(int unichar)
{
}

void Widget::keyDown(int keyCode)
{
}

void Widget::mouseMove(int x, int y)
{
    Event evt = guiSystem->createEvent(EventType::MOUSE_MOVE);
    emitEvent(evt);
}

void Widget::stateChange(State state)
{
    this->state = state;
}

void Widget::resize(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    updateAbs();

    Event evt = guiSystem->createEvent(EventType::RESIZE);
    emitEvent(evt);
}

void Widget::updateAbs()
{
    int parentX = 0, parentY = 0;

    if(parent != NULL)
    {
        parentX = parent->xAbs;
        parentY = parent->yAbs;
    }

    xAbs = parentX + x;
    yAbs = parentY + y;

    for(std::forward_list<Widget*>::iterator i = children.begin(); i != children.end(); i++)
    {
        (*i)->updateAbs();
    }
}

void Widget::focusIn()
{
    focused = true;
}

void Widget::focusOut()
{
    focused = false;
}

void Widget::setVisibility(bool visible)
{
    this->visible = visible;

    for(std::forward_list<Widget*>::iterator i = children.begin(); i != children.end(); i++)
    {
        (*i)->setVisibility(visible);
    }
}

void Widget::addChild(Widget *widget)
{
    children.push_front(widget);
}

void Widget::removeChild(Widget *widget)
{
    widget->setParent(NULL);
    //children.remove(widget);
}

void Widget::setParent(Widget *widget)
{
    widget->addChild(this);

    if(parent != NULL)
        parent->removeChild(this);

    parent = widget;
    updateAbs();
}

bool Widget::contain(int posX, int posY)
{
    if(posX >= xAbs && posX <= xAbs+w && posY >= yAbs && posY <= yAbs+h)
        return true;
    else
        return false;
}
