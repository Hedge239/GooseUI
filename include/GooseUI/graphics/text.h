#ifndef _GOOSEUI_TEXT_H_
#define _GOOSEUI_TEXT_H_

#include "GooseUI/graphics/font/fontManager.h"

namespace goose
{
    namespace core
    {
        namespace templates
        {
            namespace renderBase
            {
                struct color; // FORWARD DECLERATION
                class renderer; // FORWARD DECLERATION
            }
        }
    }

    namespace graphics
    {
        namespace font
        {
            class font; // FORWARD DECLERATION
            class layout; // FORWARD DECLERATION
        }

        class text
        {
            public:
            static void draw(core::templates::renderBase::renderer& renderer, goose::graphics::font::font* font, const std::string& text, int X, int Y, const core::templates::renderBase::color& color);
        };
    }
}

#endif /*_GOOSEUI_TEXT_H_*/

/*
    r->bindTexture(font->atlas()->getTextureID());
    for (auto& p : layout.getGlyphs()) {
        const Glyph* g = p.glyph;
        r->drawTexturedQuad(x + p.x, y - p.y, g->width, g->height, g->u0, g->v0, g->u1, g->v1, c);
    }

    --
    
    atlas->uploadToGPU(renderer);  // Calls the renderer backend function

    renderer->bindTexture(atlas->getTextureID());
    for (auto& g : layout.getGlyphs())
    renderer->drawTexturedQuad(...);
*/