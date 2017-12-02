/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "CustomWidget.h"

#include <stdexcept>
#include <iostream>

#include "GUISystem.h"

CustomWidget::CustomWidget(GUISystem *guiSystem, int x, int y) :
    Button(guiSystem, x, y, 200, 40, "")
{
    this->addEventListener(EventType::MOUSE_BUTTON_UP, static_cast<EventListener::Function>(std::bind(&CustomWidget::onClick, this, std::placeholders::_1)));
}

void CustomWidget::onClick(Event& event)
{
    try{
        this->guiSystem->createEvent(EventType::NONE);
    }
    catch(std::exception &e)
    {
        this->setText(e.what());
    }
}
