#ifndef _GOOSEUI_TEXT_H_
#define _GOOSEUI_TEXT_H_

#include "GooseUI/core/types.h"
#include "GooseUI/graphics/font/fontManager.h"

namespace goose
{
    namespace graphics
    {
        namespace font
        {
            class font; // FORWARD DECLERATION
            class layout; // FORWARD DECLERATION
        }
    }

    namespace widgets
    {
        namespace base
        {
            class text
            {
                public:
                static void draw(
                    interface::iRenderer& renderer, 
                    goose::graphics::font::font* font, 
                    const std::string& text, 
                    int X, int Y, 
                    float scale, // 1 means no scale
                    const core::types::color& color
                );
                
                static void getSize(
                    graphics::font::font* font, 
                    const std::string& text,
                    float scale,
                    int& outWidth, int& outHeight
                );
            };
        }
    }
}

#endif /*_GOOSEUI_TEXT_H_*/