#ifndef _GOOSEUI_GLYPH_H_
#define _GOOSEUI_GLYPH_H_

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
    }
}

#endif /*_GOOSEUI_GLYPH_H_*/