#ifndef _GOOSEUI_TEXT_H_
#define _GOOSEUI_TEXT_H_

#include "GooseUI/types.h"

#include <string>

namespace GooseUI
{
    namespace graphics
    {
        class text
        {
            static void _drawBitmap(absractions::iFont *font, const std::string &text, int X, int Y, float scale, const color &color);
            static void _drawSDF(absractions::iFont *font, const std::string &text, int X, int Y, float scale, const color &color);
            
            public:
            static void draw(
                absractions::iFont* font,
                const std::string& text,
                int X, int Y,
                float scale,
                const color& color
            );

            static void getSize(
                absractions::iFont* font,
                const std::string& text,
                float scale,
                int& outWidth, int& outHeight
            );
        };
    }
}

#endif /*_GOOSEUI_TEXT_H_*/