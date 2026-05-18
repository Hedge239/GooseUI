#ifndef _GOOSEUI_IFONT_H_
#define _GOOSEUI_IFONT_H_

#include "GooseUI/font/glyph.h"
#include "GooseUI/font/atlas.h"
#include "GooseUI/font/fontData.h"

#include <cstdint>
#include <string>

namespace GooseUI
{
    namespace absractions
    {
        class iFont
        {
            public:
            virtual ~iFont() = default;
            
            virtual bool load(const std::string &PathToFont, const font::fontData &fontData) = 0;
            
            virtual const font::glyph& getGlyph(uint32_t codepoint) = 0;
            virtual const font::fontData& getFontData() = 0;
            virtual font::atlas* getAtlas() = 0;
        };

        absractions::iFont* createFont();
    }
}

#endif /*_GOOSEUI_IFONT_H_*/