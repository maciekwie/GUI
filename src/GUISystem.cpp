/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "GUISystem.h"

#include <stdexcept>

#include "loggerLocator.h"
#include "EventObject.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"

using namespace gui;

GUISystem::GUISystem() :
    mouseX(0),
    mouseY(0),
    renderer(NULL),
    focus(NULL)
{
    addEventType(EventType::DISPLAY_CLOSE, static_cast<CreateEventObject>(std::bind(&GUISystem::createNull, this, std::placeholders::_1)));
    addEventType(EventType::RESIZE, static_cast<CreateEventObject>(std::bind(&GUISystem::createNull, this, std::placeholders::_1)));

    addEventType(EventType::MOUSE_MOVE, static_cast<CreateEventObject>(std::bind(&GUISystem::createMouseEvent, this, std::placeholders::_1)));
    addEventType(EventType::MOUSE_BUTTON_DOWN, static_cast<CreateEventObject>(std::bind(&GUISystem::createMouseEvent, this, std::placeholders::_1)));
    addEventType(EventType::MOUSE_BUTTON_UP, static_cast<CreateEventObject>(std::bind(&GUISystem::createMouseEvent, this, std::placeholders::_1)));

    addEventType(EventType::KEY_PRESS, static_cast<CreateEventObject>(std::bind(&GUISystem::createKeyboardEvent, this, std::placeholders::_1)));
    addEventType(EventType::KEY_DOWN, static_cast<CreateEventObject>(std::bind(&GUISystem::createKeyboardEvent, this, std::placeholders::_1)));
    addEventType(EventType::KEY_UP, static_cast<CreateEventObject>(std::bind(&GUISystem::createKeyboardEvent, this, std::placeholders::_1)));
}

GUISystem::~GUISystem()
{

}

void GUISystem::setRenderer(Renderer *renderer)
{
    this->renderer = renderer;
}

void GUISystem::render()
{
    renderer->setTarget();
    renderer->clear();

    for(std::forward_list<Widget*>::iterator i = widgets.begin(); i != widgets.end(); i++)
    {
        if((*i)->visible)
            (*i)->render(renderer);
    }
}

void GUISystem::handleEvents()
{
    while(!eventQueue.empty())
    {
        EventListener eventListener;
        Event event = eventQueue.getNextEvent(eventListener);

        eventListener(event);
    }
}

void GUISystem::mouseMove(int x, int y)
{
    mouseX = x;
    mouseY = y;

    for(std::forward_list<Widget*>::iterator i = widgets.begin(); i != widgets.end(); i++)
    {
        Widget::State state = (*i)->getState();

        if((*i)->visible && (*i)->contain(mouseX, mouseY))
        {
            if(state == Widget::STATE_UP)
            {
                (*i)->stateChange(Widget::STATE_HOVER);
            }
        }
        else
        {
            if(state == Widget::STATE_HOVER)
            {
                (*i)->stateChange(Widget::STATE_UP);
            }
        }

        (*i)->mouseMove(mouseX, mouseY);
    }
}

void GUISystem::mouseButtonUp()
{
    for(std::forward_list<Widget*>::iterator i = widgets.begin(); i != widgets.end(); i++)
    {
        if((*i)->visible && (*i)->getState() != Widget::STATE_UP)
        {
            if((*i)->contain(mouseX, mouseY))
                (*i)->stateChange(Widget::STATE_HOVER);
            else
                (*i)->stateChange(Widget::STATE_UP);
        }
    }
}

void GUISystem::mouseButtonDown()
{
    Widget *newFocus = NULL;

    for(std::forward_list<Widget*>::iterator i = widgets.begin(); i != widgets.end(); i++)
    {
        if((*i)->visible && (*i)->contain(mouseX, mouseY))
        {
            (*i)->stateChange(Widget::STATE_DOWN);
            newFocus = (*i);
        }
    }

    if(newFocus != focus)
    {
        if(focus != NULL)
        {
            focus->focusOut();
        }

        if(newFocus != NULL)
        {
            focus = newFocus;
            focus->focusIn();
        }
        else
        {
            focus = NULL;
        }
    }
}

void GUISystem::keyChar(int unichar)
{
    if(focus != NULL)
    {
        focus->keyChar(unichar);
    }
}

void GUISystem::keyDown(int keyCode)
{
    if(focus != NULL)
    {
        focus->keyDown(keyCode);
    }
}

Handle<Button> GUISystem::addButton(int x, int y, int w, int h, std::string text)
{
    Button *button = new Button(this, x, y, w, h, text);
    button->guiSystem = this;

    button->upStateColor = renderer->color(0, 0, 120);
    button->hoverStateColor = renderer->color(20, 20, 190);
    button->downStateColor = renderer->color(0, 0, 90);
    button->textColor = renderer->color(255, 255, 255);

    auto addToQueue = std::bind(&EventQueue::addToQueue, &eventQueue, std::placeholders::_1, std::placeholders::_2);
    button->setQueue(static_cast<AddToQueue>(addToQueue));

    widgets.push_front(button);

    return Handle<Button>(button);
}

Handle<TextField> GUISystem::addTextField(int x, int y, int w, int h, std::string text)
{
    TextField *textField = new TextField(this, x, y, w, h, text);
    textField->guiSystem = this;

    textField->textColor = renderer->color(0, 0, 0);

    auto addToQueue = std::bind(&EventQueue::addToQueue, &eventQueue, std::placeholders::_1, std::placeholders::_2);
    textField->setQueue(static_cast<AddToQueue>(addToQueue));

    widgets.push_front(textField);

    return Handle<TextField>(textField);
}

Handle<EditBox> GUISystem::addEditBox(int x, int y, int w, int h, bool multiline)
{
    EditBox *editBox = new EditBox(this, x, y, w, h);
    editBox->guiSystem = this;

    if(multiline)
        editBox->setMultiline();

    editBox->textColor = renderer->color(0, 0, 0);
    editBox->frameColor = renderer->color(0, 0, 0);
    editBox->backgroundColor = renderer->color(255, 255, 255);
    editBox->cursorColor = renderer->color(0, 0, 0);

    auto addToQueue = std::bind(&EventQueue::addToQueue, &eventQueue, std::placeholders::_1, std::placeholders::_2);
    editBox->setQueue(static_cast<AddToQueue>(addToQueue));

    widgets.push_front(editBox);

    return Handle<EditBox>(editBox);
}

Handle<Scrollbar> GUISystem::addScrollbar(int x, int y, int w, int h)
{
    Scrollbar *scrollbar = new Scrollbar(this, x, y, w, h);
    scrollbar->guiSystem = this;

    scrollbar->backgroundColor = renderer->color(255, 255, 255);
    scrollbar->frameColor = renderer->color(0, 0, 0);

    auto addToQueue = std::bind(&EventQueue::addToQueue, &eventQueue, std::placeholders::_1, std::placeholders::_2);
    scrollbar->setQueue(static_cast<AddToQueue>(addToQueue));

    widgets.push_front(scrollbar);

    return Handle<Scrollbar>(scrollbar);
}

Handle<Widget> GUISystem::addWidget(CreateWidget createWidget, bool setEventQueue)
{
    Widget *widget = createWidget(this);
    widget->guiSystem = this;

    widgets.push_front(widget);

    if(setEventQueue)
    {
        auto addToQueue = std::bind(&EventQueue::addToQueue, &eventQueue, std::placeholders::_1, std::placeholders::_2);
        widget->setQueue(static_cast<AddToQueue>(addToQueue));
    }

    return Handle<Widget>(widget);
}

Event GUISystem::createEvent(EventType eventType)
{
    auto iter = createEvtObjFuncs.find(eventType);

    if(iter == createEvtObjFuncs.end())
        throw std::invalid_argument("Type not found.");

    EventObject *evtObj = iter->second(NULL);

    Event event(eventType, evtObj);

    return event;
}

Event GUISystem::cloneEvent(const Event& _event)
{
    Event event;
    event.type = _event.type;

    auto iter = createEvtObjFuncs.find(event.type);

    if(iter == createEvtObjFuncs.end())
        throw std::invalid_argument("Type not found.");

    EventObject *evtObj = iter->second(_event.obj);

    event.obj = evtObj;

    return event;
}

EventObject* GUISystem::createEventObject(EventObject* obj)
{
    EventObject *evtObj;

    if(obj == NULL)
        evtObj = new EventObject();
    else
        evtObj = new EventObject(*obj);

    return evtObj;
}

EventObject* GUISystem::createMouseEvent(EventObject* obj)
{
    MouseEvent *evtObj;

    if(obj == NULL)
    {
        evtObj = new MouseEvent();
        evtObj->mouseX = mouseX;
        evtObj->mouseY = mouseY;
    }
    else
        evtObj = new MouseEvent(*static_cast<MouseEvent*>(obj));

    return evtObj;
}

EventObject* GUISystem::createKeyboardEvent(EventObject* obj)
{
    KeyboardEvent *evtObj;

    if(obj == NULL)
        evtObj = new KeyboardEvent();
    else
        evtObj = new KeyboardEvent(*static_cast<KeyboardEvent*>(obj));

    return evtObj;
}

void GUISystem::addEventType(EventType eventType, CreateEventObject createFunc)
{
    if(createEvtObjFuncs.find(eventType) != createEvtObjFuncs.end())
    {
        throw std::runtime_error("Type already registered.");
    }

    createEvtObjFuncs.emplace(eventType, createFunc);
}
