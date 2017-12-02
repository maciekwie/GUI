/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef GUISYSTEM_H
#define GUISYSTEM_H

#include <forward_list>
#include <map>
#include <string>

#include "Button.h"
#include "EditBox.h"
#include "Event.h"
#include "EventQueue.h"
#include "Handle.h"
#include "Renderer.h"
#include "Scrollbar.h"
#include "TextField.h"
#include "Widget.h"

//! GUI library's name space.

namespace gui
{

typedef std::function<Widget*(GUISystem*)> CreateWidget;
typedef std::function<EventObject*(EventObject*)> CreateEventObject;

//! Manages creating widgets and events and provides routines governing GUI mechanisms.

class GUISystem
{
    public:
        typedef std::map<EventType, CreateEventObject> Map;

        GUISystem();
        ~GUISystem();

        /** \brief Sets Renderer object to be used.
         *
         * \param renderer Renderer* pointer
         *
         */
        void setRenderer(Renderer *renderer);

        /** \brief Returns associated Renderer object.
         *
         * \return Renderer* pointer
         *
         */
        Renderer* getRenderer() { return renderer; }

        /** \brief
         *  Renders the gui.
         */
        void render();

        /** \brief Affiliates event identifier with creating function.
         *
         * \param eventType Event type identifier
         * \param createFunc Function returning EventObject* pointer
         *
         */
        void addEventType(EventType eventType, CreateEventObject createFunc);

        /** \brief
         *  Calls functions associated with events.
         */
        void handleEvents();

        /** \brief Updates gui state. To be called when mouse is moved.
         */
        void mouseMove(int x, int y);

        /** \brief Updates gui state. To be called when mouse button is released.
         */
        void mouseButtonUp();

        /** \brief Updates gui state. To be called when mouse is pressed.
         */
        void mouseButtonDown();

        /** \brief Updates gui state. To be called when a character is typed or repeated.
         */
        void keyChar(int unichar);

        /** \brief Updates gui state. To be called when a key is pressed.
         */
        void keyDown(int keyCode);

        /** \brief Creates Button widget and assigns it to the gui.
         *
         * \param x X coordinate
         * \param y Y coordinate
         * \param w Width
         * \param h Height
         * \param text Text to be displayed
         * \return Handle to the Button object
         *
         */
        Handle<Button> addButton(int x, int y, int w, int h, std::string text);

        /** \brief Creates TextField widget and assigns it to the gui.
         *
         * \param x X coordinate
         * \param y Y coordinate
         * \param w Width
         * \param h Height
         * \param text Text to be displayed
         * \return Handle to the TextField object
         *
         */
        Handle<TextField> addTextField(int x, int y, int w, int h, std::string text);

        /** \brief Creates EditBox widget and assigns it to the gui.
         *
         * \param x X coordinate
         * \param y Y coordinate
         * \param w Width
         * \param h Height
         * \param multiline Are multiple lines allowed.
         * \return Handle to the EditBox object
         *
         */
        Handle<EditBox> addEditBox(int x, int y, int w, int h, bool multiline = false);

        /** \brief Creates Scrollbar widget and assigns it to the gui.
         *
         * \param x X coordinate
         * \param y Y coordinate
         * \param w Width
         * \param h Height
         * \return Handle to the Scrollbar object
         *
         */
        Handle<Scrollbar> addScrollbar(int x, int y, int w, int h);

        /** \brief Generic function for adding custom widgets.
         *
         * \param createWidget X Function creating widget.
         * \param setEventQueue If true, sets widget's addToQueue function.
         * \return Handle to the widget
         *
         */
        Handle<Widget> addWidget(CreateWidget createWidget, bool setEventQueue);

        /** \brief Creates an event that can be emitted.
         *
         * \param eventType Type of event
         * \return Event object
         *
         */
        Event createEvent(EventType eventType);

        /** \brief Creates a copy of an Event object.
         *
         * \param event Event object to be copied
         * \return Event object
         *
         */
        Event cloneEvent(const Event& event);

        /** \brief Returns null pointer.
         *
         * \param obj Irrelevant here
         * \return Null pointer
         *
         *  Used for registering event types with no own properties.
         */
        EventObject* createNull(EventObject* obj = NULL) {  return NULL; };

        /** \brief  Creates an EventObject object.
         *
         * \param obj EventObject to copy. Creates new object when NULL.
         * \return Pointer to the created object
         *
         */
        EventObject* createEventObject(EventObject* obj = NULL);

        /** \brief  Creates an MouseEvent object with default values.
         *
         * \param obj EventObject to copy. Creates new object when NULL.
         * \return Pointer to the created object
         *
         */
        EventObject* createMouseEvent(EventObject* obj = NULL);

        /** \brief  Creates an KeyboardEvent object.
         *
         * \param obj EventObject to copy. Creates new object when NULL.
         * \return Pointer to the created object
         */
        EventObject* createKeyboardEvent(EventObject* obj = NULL);

        int mouseX; /// Mouse x coordinate
        int mouseY; /// Mouse y coordinate

    protected:

    private:
        Renderer *renderer;
        std::forward_list<Widget*> widgets;
        Map createEvtObjFuncs;
        EventQueue eventQueue;

        Widget *focus;
};

}

#endif // GUISYSTEM_H
