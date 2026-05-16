#ifndef _GOOSEUI_GLYPH_H_
#define _GOOSEUI_GLYPH_H_

#include <cstdint>
#include <vector>

namespace GooseUI
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

        struct glyphData
        {
            glyph metrics;
            std::vector<uint8_t> pixels;
            int pitch;
        };
    }
}

#endif /*_GOOSEUI_GLYPH_H_*/