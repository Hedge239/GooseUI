#ifndef _GOOSEUI_WIN32_DIRECTWRITE_H_
#define _GOOSEUI_WIN32_DIRECTWRITE_H_

#include "GooseUI/graphics/font/font.h"
#include "GooseUI/graphics/font/fontAtlas.h"

#include <unordered_map>
#include <cstdint>

#include <dwrite.h>
#include <wrl.h>

namespace goose
{
    namespace platform
    {
        namespace gWin32
        {
            // I decided to naem ti DirectWrite instead of font as a "just in case"
            class gWin32_DirectWrite : public graphics::font::font
            {
                Microsoft::WRL::ComPtr<IDWriteFactory> _factory;
                Microsoft::WRL::ComPtr<IDWriteFontFace> _face;
                Microsoft::WRL::ComPtr<IDWriteFontFile> _fontFile;

                graphics::font::atlas _atlas;
                std::unordered_map<uint32_t, graphics::font::glyph> _glyphs;

                float _size = 0.0f;
                bool _initialized = false;

                public:
                gWin32_DirectWrite();

                // Overides
                bool load(const std::string& path, int pixelSize) override;

                const graphics::font::glyph& getGlyph(uint32_t codepoint) override;
                graphics::font::atlas* getAtlas() override;
            };
        }
    }
}

#endif /*_GOOSEUI_WIN32_DIRECTWRITE_H_*/