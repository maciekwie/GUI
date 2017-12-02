/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "Scrollbar.h"

#include <iostream>

#include "GUISystem.h"

using namespace gui;

Scrollbar::Scrollbar(GUISystem *guiSystem, int x, int y, int w, int h) :
    Widget(x, y, w, h),
    upButton(guiSystem->addButton(0, h-15, w, 15, "")),
    downButton(guiSystem->addButton(0, 0, w, 15, "")),
    slideButton(guiSystem->addButton(0, 20, w, 20, "")),
    mouseMoveListenerId(0),
    sliderPosition(0),
    sliderLength(0.4)
{
    downButton->setParent(this);
    auto downClickEventListener = std::bind(&Scrollbar::downButtonClick, this, std::placeholders::_1);
    downButton->addEventListener(EventType::MOUSE_BUTTON_UP, static_cast<EventListener::Function>(downClickEventListener));

    upButton->setParent(this);
    auto upClickEventListener = std::bind(&Scrollbar::upButtonClick, this, std::placeholders::_1);
    upButton->addEventListener(EventType::MOUSE_BUTTON_UP, static_cast<EventListener::Function>(upClickEventListener));

    slideButton->setParent(this);

    auto sliderDownEventListener = std::bind(&Scrollbar::sliderMouseDown, this, std::placeholders::_1);
    slideButton->addEventListener(EventType::MOUSE_BUTTON_DOWN, static_cast<EventListener::Function>(sliderDownEventListener));

    auto sliderUpEventListener = std::bind(&Scrollbar::sliderMouseUp, this, std::placeholders::_1);
    slideButton->addEventListener(EventType::MOUSE_BUTTON_UP, static_cast<EventListener::Function>(sliderUpEventListener));

    setSlider(sliderPosition);
}

void Scrollbar::render(Renderer *renderer)
{
    int x = xAbs, y = yAbs;
    renderer->setTarget(x, y, w, h);

    renderer->drawFilledRect(0, 0, w, h, backgroundColor);
    renderer->drawRect(1, 1, w-1, h-1, frameColor, 2);
}

void Scrollbar::downButtonClick(Event& event)
{
    setSlider(sliderPosition - 0.1);
}

void Scrollbar::upButtonClick(Event& event)
{
    setSlider(sliderPosition + 0.1);
}

void Scrollbar::sliderMouseDown(Event& _event)
{
    if(_event.getType() != EventType::MOUSE_BUTTON_DOWN)
        return;

    MouseEvent *event = _event.getEventObject<MouseEvent>();
    holdPointX = event->mouseX;
    holdPointY = event->mouseY;
    sliderPrevPos = sliderPosition;

    if(mouseMoveListenerId != 0)
        return;

    auto listenerFunction = std::bind(&Scrollbar::sliderMouseMove, this, std::placeholders::_1);
    mouseMoveListenerId = slideButton->addEventListener(EventType::MOUSE_MOVE,
        static_cast<EventListener::Function>(listenerFunction));
}

void Scrollbar::sliderMouseUp(Event& _event)
{
    if(_event.getType() != EventType::MOUSE_BUTTON_UP)
        return;

    if(mouseMoveListenerId == 0)
        return;

    slideButton->removeEventListener(mouseMoveListenerId);
    mouseMoveListenerId = 0;
}

void Scrollbar::sliderMouseMove(Event& _event)
{
    if(_event.getType() != EventType::MOUSE_MOVE)
        return;

    MouseEvent *event = _event.getEventObject<MouseEvent>();

    //float x = event->mouseX - holdPointX;
    float y = event->mouseY - holdPointY;
    float h = this->h - 30 - sliderLength*(this->h-30);
    float posChange = y / h;

    setSlider(sliderPrevPos + posChange);
}

void Scrollbar::setSlider(float position)
{
    sliderPosition = (position > 1) ? 1 : ((position < 0) ? 0 : position);

    int h = sliderLength * (this->h - 30);
    int y = sliderPosition * (this->h - 30 - h) + 15;
    slideButton->resize(0, y, this->w, h);
}

void Scrollbar::setSliderLength(float length)
{
    sliderLength = (length > 1) ? 1 : ((length < 0) ? 0 : length);

    if(sliderPosition > 1-sliderLength)
        sliderPosition = (1-sliderLength < 0) ? 0 : 1-sliderLength;

    setSlider(sliderPosition);
}
