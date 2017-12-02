/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "TextField.h"

using namespace gui;

TextField::TextField(GUISystem *guiSystem, int x, int y, int w, int h, std::string text) :
    Widget(x, y, w, h),
    text(text)
{
}

void TextField::render(Renderer *renderer)
{
    int x = xAbs, y = yAbs;
    renderer->setTarget(x, y, w, h);

    renderer->drawText(0, 0, text, textColor);
}

void TextField::setText(const std::string &text)
{
    this->text = text;
}

std::string TextField::getText()
{
    return text;
}
