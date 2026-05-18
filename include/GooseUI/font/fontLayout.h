#ifndef _GOOSEUI_FONTLAYOUT_H_
#define _GOOSEUI_FONTLAYOUT_H_

#include "GooseUI/font/glyph.h"
#include "GooseUI/abstractions/iFont.h"

#include <vector>
#include <string>

namespace GooseUI 
{
    namespace font
    {
        class layout
        {
            std::vector<glyphPos> _glyphsPosistions;
            
            public:
            void setText(const std::string& text, absractions::iFont* font);
            const std::vector<glyphPos>& getGlyphs() const;
        };
    }
}

#endif /*_GOOSEUI_FONTLAYOUT_H_*/