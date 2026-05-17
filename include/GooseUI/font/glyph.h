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

            float paddingLeft   = 0.0f;
            float paddingTop    = 0.0f;
            float paddingRight  = 0.0f;
            float paddingBottom = 0.0f;
        };
    }
}

#endif /*_GOOSEUI_GLYPH_H_*/