/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef APP_H
#define APP_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "Button.h"
#include "CustomWidget.h"
#include "EditBox.h"
#include "Event.h"
#include "events.h"
#include "GUISystem.h"
#include "Handle.h"
#include "Renderer.h"
#include "TextField.h"

using namespace gui;

//! Application's main class.

class App
{
    public:
        /** \brief
         *  Constructor. Parses command-line arguments.
         *
         * \param argc Argument count
         * \param argv Argument vector
         *
         */
        App(int argc, char **argv);

        virtual ~App();

        /** \brief
         *  Initializes Allegro5 library.
         */
        void initAllegro();

        /** \brief
         *  Initializes interface and sets the GUI.
         */
        void init();

        /** \brief
         *  Application's main loop.
         *
         *  \param waitForEvent If true, blocks the application until an Allegro's event come.
         *  \return Has the application finished.
         */
        bool loop(bool waitForEvent = false);

        //Widget functions
        void setButtonOnClick(Event& event);
        Widget *createWidget(GUISystem *guiSystem);

    protected:

    private:
        ALLEGRO_DISPLAY *display;
        ALLEGRO_EVENT_QUEUE *queue;
        ALLEGRO_FONT *font;

        GUISystem *guiSystem;
        Renderer *renderer;

        //Widgets
        Handle<EditBox> editBox;
        Handle<TextField> textField;
        Handle<Button> setButton;
        Handle<EditBox> multilineEdit;
        Handle<Widget> customWidget;

        /** \brief
         *  Used for preventing multiple instances.
         */
        static bool initialized;
};

#endif // APP_H
