/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "Button.h"

#include "GUISystem.h"
#include "Renderer.h"

using namespace gui;

Button::Button(GUISystem *guiSystem, int x, int y, int w, int h, std::string text) :
    Widget(x, y, w, h),
    text(text)
{
    this->guiSystem = guiSystem;
}

void Button::render(Renderer *renderer)
{
    int x = xAbs, y = yAbs;
    renderer->setTarget(x, y, w, h);

    if(state == Widget::STATE_UP)
        renderer->drawFilledRect(0, 0, w, h, upStateColor);
    else if(state == Widget::STATE_HOVER)
        renderer->drawFilledRect(0, 0, w, h, hoverStateColor);
    else if(state == Widget::STATE_DOWN)
        renderer->drawFilledRect(0, 0, w, h, downStateColor);

    renderer->drawText(0, 0, text, textColor);
}

void Button::stateChange(Widget::State newState)
{
    if(state == Widget::STATE_DOWN && (newState == Widget::STATE_UP || newState == Widget::STATE_HOVER))
    {
        Event evt = this->guiSystem->createEvent(EventType::MOUSE_BUTTON_UP);
        emitEvent(evt);
    }
    else if(newState == Widget::STATE_DOWN)
    {
        Event evt = this->guiSystem->createEvent(EventType::MOUSE_BUTTON_DOWN);
        emitEvent(evt);
    }
    else if(newState == Widget::STATE_HOVER)
    {
    }

    state = newState;
}

void Button::setText(const std::string &text)
{
    this->text = text;
}

