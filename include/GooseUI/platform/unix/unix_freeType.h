#ifndef _GOOSEUI_UNIX_FREETYPE_H_
#define _GOOSEUI_UNIX_FREETYPE_H_

#include "GooseUI/graphics/font/font.h"
#include "GooseUI/graphics/font/fontAtlas.h"

#include <unordered_map>
#include <cstdint>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace goose
{
    namespace platform
    {
        namespace gUnix
        {
            class gUnix_FreeType : public graphics::font::font
            {
                FT_Library _library = nullptr;
                FT_Face _face = nullptr;

                graphics::font::atlas _atlas;
                std::unordered_map<uint32_t, graphics::font::glyph> _glyphs;

                float _size = 0.0f;
                bool _initialized = false;

                public:
                gUnix_FreeType();

                // Overides
                bool load(const std::string& path, int pixelSize) override;

                const graphics::font::glyph& getGlyph(uint32_t codepoint) override;
                graphics::font::atlas* getAtlas() override;
            };
        }
    }
}

#endif /*_GOOSEUI_UNIX_FREETYPE_H_*/