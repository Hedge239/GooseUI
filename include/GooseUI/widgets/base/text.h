#ifndef _GOOSEUI_TEXT_H_
#define _GOOSEUI_TEXT_H_

#include "GooseUI/graphics/font/fontManager.h"

namespace goose
{
    namespace core
    {
        namespace templates
        {
            namespace renderBase
            {
                struct color; // FORWARD DECLERATION
                class renderer; // FORWARD DECLERATION
            }
        }
    }

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
                static void draw(core::templates::renderBase::renderer& renderer, goose::graphics::font::font* font, const std::string& text, int X, int Y, const core::templates::renderBase::color& color);
            };
        }
    }
}

#endif /*_GOOSEUI_TEXT_H_*/