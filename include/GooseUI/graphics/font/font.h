#ifndef _GOOSEUI_FONT_H_
#define _GOOSEUI_FONT_H_

#include "GooseUI/graphics/font/fontAtlas.h"

#include <cstdint>
#include <memory>
#include <string>

namespace goose 
{
    namespace graphics
    {
        namespace font
        {
            struct glyph
            {
                float xAdvance;
                float xOffset, yOffset;
                float width, height;
                float u0, u1, v0, v1;
            };

            class font
            {
                public:
                virtual ~font() = default;

                virtual bool load(const std::string& path, int pixelSize) = 0;
                
                virtual const glyph& getGlyph(uint32_t codepoint) = 0;
                virtual atlas* getAtlas() = 0;
            };

            std::unique_ptr<font> createFont();
        }
    }
}

#endif /*_GOOSEUI_FONT_H_*/