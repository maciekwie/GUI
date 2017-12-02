/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "EventListener.h"

using namespace gui;

EventListener::EventListener(Function function)
{
    bind(function);
}

void EventListener::bind(Function& function)
{
    func = function;
}

void EventListener::operator() (Event& event)
{
    func(event);
}
