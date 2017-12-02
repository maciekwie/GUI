/*
 *    Copyright (c) 2017 by Maciej Wiecierzewski
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <string>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>

namespace gui
{

typedef ALLEGRO_COLOR Color;

//! Class that provides rendering functions for widgets.

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();

        /** \brief Sets font to be used by text drawing functions.
         */
        void setFont(ALLEGRO_FONT *font);

        /** \brief
         */
        void setBuffer(ALLEGRO_BITMAP *bitmap);

        /** \brief Returns Color object to be passed to drawing functions.
         */
        Color color(unsigned char r, unsigned char g, unsigned char b);

        /** \brief Sets drawing target to the entire buffer bitmap's area.
         */
        void setTarget();

        /** \brief Restricts drawing area to the buffer's region.
         * param x Ta
         */
        void setTarget(int x, int y, int w, int h);

        /** \brief Clears buffer with background color.
         */
        void clear();

        void drawFilledRect(int x1, int y1, int x2, int y2, Color color);
        void drawRect(int x1, int y1, int x2, int y2, Color color, int thickness);
        void drawText(int x, int y, std::string text, Color color);
        void drawMultilineText(int x, int y, int maxWidth, float lineHeight, std::string text, Color color);
        void drawLine(int x1, int y1, int x2, int y2, Color color, int thickness);
        int getTextWidth(std::string text);
        int getLineHeight();

    protected:

    private:
        ALLEGRO_FONT *font;
        ALLEGRO_BITMAP *buffer;
        ALLEGRO_BITMAP *targetBitmap;
};

}

#endif // RENDERER_H
