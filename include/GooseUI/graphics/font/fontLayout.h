#ifndef _GOOSEUI_FONTLAYOUT_H_
#define _GOOSEUI_FONTLAYOUT_H_

#include "GooseUI/graphics/font/font.h"

#include <vector>
#include <string>

namespace goose
{
    namespace graphics
    {
        namespace font
        {
            struct glyphPos
            {
                const glyph* g; // Changed because freetype :<
                float x, y;
            };

            class layout
            {
                std::vector<glyphPos> _glyphsPosistions;

                public:
                void setText(const std::string& text, font* font);
                const std::vector<glyphPos>& getGlyphs() const;
            };
        }
    }
}

#endif /*_GOOSEUI_FONTLAYOUT_H_*/