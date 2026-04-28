#ifndef _GOOSEUI_IFONT_H_
#define _GOOSEUI_IFONT_H_

#include "GooseUI/font/glyph.h"
#include "GooseUI/font/atlas.h"
#include "GooseUI/font/fontData.h"

#include <cstdint>

namespace GooseUI
{
    namespace absractions
    {
        class iFont
        {
            public:
            virtual ~iFont() = default;
            
            virtual bool createFont(const font::fontData &fontData);
            
            virtual const font::glyph& getGlyph(uint32_t codepoint) = 0;
            virtual font::atlas* getAtlas() = 0;
        };
    }
}

#endif /*_GOOSEUI_IFONT_H_*/