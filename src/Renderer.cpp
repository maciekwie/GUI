/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#include "Renderer.h"

#include <allegro5/allegro_primitives.h>

using namespace gui;

Renderer::Renderer() :
    font(NULL),
    buffer(NULL),
    targetBitmap(NULL)
{
}

Renderer::~Renderer()
{
}

void Renderer::setFont(ALLEGRO_FONT *font)
{
    this->font = font;
}

void Renderer::setBuffer(ALLEGRO_BITMAP *bitmap)
{
    buffer = bitmap;
}

Color Renderer::color(unsigned char r, unsigned char g, unsigned char b)
{
    return al_map_rgb(r, g, b);
}

void Renderer::setTarget()
{
    if(targetBitmap != NULL)
    {
        al_destroy_bitmap(targetBitmap);
        targetBitmap = NULL;
    }

    al_set_target_bitmap(buffer);
}

void Renderer::setTarget(int x, int y, int w, int h)
{
    if(targetBitmap != NULL)
    {
        al_destroy_bitmap(targetBitmap);
        targetBitmap = NULL;
    }

    targetBitmap = al_create_sub_bitmap(buffer, x, y, w, h);
    al_set_target_bitmap(targetBitmap);
}

void Renderer::clear()
{
    al_clear_to_color(al_map_rgb(255, 255, 255));
}

void Renderer::drawFilledRect(int x1, int y1, int x2, int y2, Color color)
{
    al_draw_filled_rectangle(x1, y1, x2, y2, color);
}

void Renderer::drawRect(int x1, int y1, int x2, int y2, Color color, int thickness)
{
    al_draw_rectangle(x1, y1, x2, y2, color, thickness);
}

void Renderer::drawText(int x, int y, std::string text, Color color)
{
    al_draw_text(font, color, x, y, 0, text.c_str());
}

void Renderer::drawMultilineText(int x, int y, int maxWidth, float lineHeight, std::string text, Color color)
{
    al_draw_multiline_text(font, color, x, y, maxWidth, lineHeight, 0, text.c_str());
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, Color color, int thickness)
{
    al_draw_line(x1, y1, x2, y2, color, thickness);
}

int Renderer::getTextWidth(std::string text)
{
    return al_get_text_width(font, text.c_str());
}

int Renderer::getLineHeight()
{
    return al_get_font_line_height(font);
}
