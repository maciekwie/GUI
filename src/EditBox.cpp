/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "EditBox.h"

#include <iostream>

#include "GUISystem.h"
#include "Renderer.h"

using namespace gui;

EditBox::EditBox(GUISystem *guiSystem, int x, int y, int w, int h) :
    Widget(x, y, w, h),
    backspaceCode(8),
    vScrollbar(guiSystem->addScrollbar(w-15, 0, 15, h)),
    hScrollbar(guiSystem->addScrollbar(0, h-15, w, 15)),
    cursorPos(0),
    cursorLine(0),
    lines(0),
    lineHeight(35),
    multiline(false),
    vScroll(false),
    hScroll(false)
{
    hScrollbar->setParent(this);
    hScrollbar->setVisibility(false);

    vScrollbar->setParent(this);
    vScrollbar->setVisibility(false);
}

void EditBox::render(Renderer *renderer)
{
    int x = xAbs, y = yAbs;
    renderer->setTarget(x, y, w, h);

    lineHeight = renderer->getLineHeight();

    int cursorX, cursorY;
    getCursorXY(renderer, cursorX, cursorY);

    int textPos = 0;
    float textArea = (lines+1) * lineHeight;

    if(textArea > h)
        textPos = vScrollbar->getSliderPosition() * (h - textArea);

    renderer->drawFilledRect(0, 0, w, h, backgroundColor);
    renderer->drawRect(1, 1, w-1, h-1, frameColor, 2);
    renderer->drawMultilineText(4, textPos, w, 35, text, textColor);

    if(focused)
    {
        renderer->drawLine(cursorX+4, textPos+cursorY+2, cursorX+4, textPos+cursorY+lineHeight, cursorColor, 1);
    }
}

void EditBox::keyChar(int unichar)
{
    if(unichar <= 26)
        return;

    char character = static_cast<char>(unichar);
    std::string str;
    str.push_back(character);

    text.insert(cursorPos, str);
    cursorPos++;

    updateScrollbars();
    findCursorLine();
    countLines();
}

void EditBox::keyDown(int keyCode)
{
    if(keyCode == KEY_BACKSPACE)
    {
        if(cursorPos > 0)
        {
            text.erase(--cursorPos, 1);
        }
    }
    else if((keyCode == KEY_LEFT) && cursorPos > 0)
    {
        cursorPos--;
    }
    else if((keyCode == KEY_RIGHT) && cursorPos < text.length())
    {
        cursorPos++;
    }
    else if(keyCode == KEY_ENTER && multiline)
    {
        text.insert(cursorPos, "\n");
        cursorPos++;
    }

    findCursorLine();
    countLines();
    updateScrollbars();
}

void EditBox::setMultiline()
{
    multiline = true;
}

void EditBox::setText(const std::string &text)
{
    this->text = text;
    countLines();
}

std::string EditBox::getText()
{
    return text;
}

void EditBox::updateScrollbars()
{
    float textArea = (lines+1) * lineHeight;

    if(textArea > h)
    {
        if(!vScroll)
        {
            vScroll = true;
            vScrollbar->setVisibility(true);
        }

        float sliderLengh = h / textArea;
        vScrollbar->setSliderLength(sliderLengh);
    }
    else if(vScroll)
    {
        vScroll = false;
        vScrollbar->setVisibility(false);
    }
}

void EditBox::getCursorXY(Renderer *renderer, int& cursorX, int& cursorY)
{
    if(cursorPos == 0)
    {
        cursorX = 0;
        cursorY = 0;
        return;
    }

    int lineBegin;
    for(lineBegin = cursorPos-1; lineBegin > 0 && text[lineBegin] != '\n'; lineBegin--) {}
    if(text[lineBegin] == '\n')
        lineBegin++;

    std::string line = text.substr(lineBegin, cursorPos - lineBegin);

    cursorX = renderer->getTextWidth(line);
    cursorY = cursorLine * lineHeight;
}

void EditBox::findCursorLine()
{
    cursorLine = 0;

    for(int i = cursorPos-1; i > 0; i--)
    {
        if(text[i] == '\n')
            cursorLine++;
    }
}

void EditBox::countLines()
{
    lines = 1;

    for(unsigned int i = 0; i < text.length(); i++)
    {
        if(text[i] == '\n')
            lines++;
    }
}
