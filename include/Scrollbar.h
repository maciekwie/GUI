/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "Button.h"
#include "EventListener.h"
#include "Handle.h"
#include "MouseEvent.h"
#include "Renderer.h"
#include "Widget.h"

namespace gui
{

class GUISystem;

//! Scrollbar widget. Has a bar and it scrolls!

class Scrollbar : public Widget
{
    public:
        Scrollbar(GUISystem *guiSystem, int x, int y, int w, int h);
        virtual ~Scrollbar() {};

        void render(Renderer *renderer);

        void downButtonClick(Event& event);
        void upButtonClick(Event& event);
        void sliderMouseDown(Event& event);
        void sliderMouseUp(Event& event);
        void sliderMouseMove(Event& event);

        void setSlider(float position);
        void setSliderLength(float length);
        float getSliderPosition() { return sliderPosition; }

    protected:
        Color backgroundColor;
        Color frameColor;

    private:
        Handle<Button> upButton;
        Handle<Button> downButton;
        Handle<Button> slideButton;

        EventListener::Id mouseMoveListenerId;

        float sliderPosition;
        float sliderLength;
        int holdPointX;
        int holdPointY;
        float sliderPrevPos;

    friend class GUISystem;
};

}

#endif // SCROLLBAR_H
