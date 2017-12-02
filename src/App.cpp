/*
 *    Copyright (c) 2017 by Maciej Więcierzewski
 */

#include "App.h"

#include <stdexcept>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

bool App::initialized = false;

App::App(int argc, char **argv) :
    display(NULL),
    queue(NULL)
{
    if(initialized)
        throw std::logic_error("Already initialized.");

    initialized = true;
}

App::~App()
{
    if(queue != NULL)
        al_destroy_event_queue(queue);
    if(display != NULL)
        al_destroy_display(display);
}

void App::initAllegro()
{
    if(!al_init())
        throw std::runtime_error("al_init error.");

    if(!al_init_primitives_addon())
        throw std::runtime_error("al_init_primitives_addon error.");
    if(!al_init_image_addon())
        throw std::runtime_error("al_init_image_addon error.");
    if(!al_init_font_addon())
        throw std::runtime_error("al_init_font_addon error.");
    if(!al_init_ttf_addon())
        throw std::runtime_error("al_init_ttf_addon error.");

    if(!al_install_keyboard())
        throw std::runtime_error("al_install_keyboard error.");
    if(!al_install_mouse())
        throw std::runtime_error("al_install_mouse error.");
}

void App::init()
{
    display = al_create_display(640, 480);
    if(!display)
        throw std::runtime_error("al_create_display error.");

    font = al_load_font("LSANSD.TTF", 30, 0);
    if(!font)
        throw std::runtime_error("Font \"LSANSD.TTF\" not loaded.");

    guiSystem = new GUISystem();
    renderer = new Renderer();

    queue = al_create_event_queue();
    if(!queue)
        throw std::runtime_error("al_create_event_queue error.");

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());

    renderer->setFont(font);
    renderer->setBuffer(al_get_backbuffer(display));
    guiSystem->setRenderer(renderer);

    editBox = guiSystem->addEditBox(20, 20, 220, 40);
    textField = guiSystem->addTextField(20, 80, 310, 40, "^ type something");
    setButton = guiSystem->addButton(260, 20, 70, 40, "set");
    multilineEdit = guiSystem->addEditBox(20, 170, 300, 150, true);
    customWidget = guiSystem->addWidget(static_cast<CreateWidget>(
            std::bind(&App::createWidget, this, std::placeholders::_1)
            ), true);

    auto eventListener = std::bind(&App::setButtonOnClick, this, std::placeholders::_1);
    setButton->addEventListener(EventType::MOUSE_BUTTON_UP, static_cast<EventListener::Function>(eventListener));
}

bool App::loop(bool waitForEvent)
{
    //rendering
    guiSystem->render();
    al_flip_display();

    if(waitForEvent)
        al_wait_for_event(queue, NULL);

    //event loop
    bool loop = true;
    ALLEGRO_EVENT event;
    while(al_get_next_event(queue, &event))
    {
        if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            guiSystem->mouseMove(event.mouse.x, event.mouse.y);
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            guiSystem->mouseButtonDown();
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            guiSystem->mouseButtonUp();
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            guiSystem->keyDown(event.keyboard.keycode);
        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP)
        {
        }
        else if(event.type == ALLEGRO_EVENT_KEY_CHAR)
        {
            guiSystem->keyChar(event.keyboard.unichar);
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
        {
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY)
        {
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
        {
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            loop = false;
            break;
        }

        guiSystem->handleEvents();
    }

    return loop;
}

void App::setButtonOnClick(Event& event)
{
    std::string text = editBox->getText();
    textField->setText(text);
}

Widget* App::createWidget(GUISystem *guiSystem)
{
    CustomWidget *widget = new CustomWidget(guiSystem, 400, 20);

    widget->setText("test");

    Renderer *renderer = guiSystem->getRenderer();
    widget->upStateColor = renderer->color(120, 0, 0);
    widget->hoverStateColor = renderer->color(190, 20, 20);
    widget->downStateColor = renderer->color(90, 0, 0);
    widget->textColor = renderer->color(255, 255, 20);

    return widget;
}
