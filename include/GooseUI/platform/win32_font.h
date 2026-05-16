#ifndef _GOOSEUI_WIN32_FONT_H_
#define _GOOSEUI_WIN32_FONT_H_

#include "GooseUI/abstractions/iFont.h"

#include <dwrite.h>
#include <wrl.h>

namespace GooseUI
{
    namespace platform
    {
        class win32_font : public absractions::iFont
        {
            Microsoft::WRL::ComPtr<IDWriteFontFace> _face;
            Microsoft::WRL::ComPtr<IDWriteFontFile> _fontFile;

            public:
            win32_font();

            // Overides
            bool load(const font::fontData &fontData) override;

            const font::glyph& getGlyph(uint32_t codepoint) override;
            font::atlas* getAtlas() override;
        };
    }
}

#endif /*_GOOSEUI_WIN32_FONT_H_*/