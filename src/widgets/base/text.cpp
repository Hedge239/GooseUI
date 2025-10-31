#include "GooseUI/widgets/base/text.h"

#include "GooseUI/graphics/font/fontLayout.h"
#include "GooseUI/graphics/font/font.h"

#include "GooseUI/core/templates/renderBase.h"


namespace goose::widgets::base
{
    void text::draw(core::templates::renderBase::renderer& renderer, graphics::font::font* font, const std::string& text, int X, int Y, const core::templates::renderBase::color& color)
    {
        graphics::font::atlas& atlas = *font->getAtlas();
        renderer.uploadFontAtlas(atlas);

        graphics::font::layout layout;
        layout.setText(text, font);

        for(const auto& gp : layout.getGlyphs())
        {
            if (gp.glyph->width == 0 || gp.glyph->height == 0) { continue; }
            renderer.drawTextureQuad(atlas.getID(), X, Y, gp.glyph->width, -gp.glyph->height, gp.glyph->u0, gp.glyph->u1, gp.glyph->v0, gp.glyph->v1, color);

            X += (gp.glyph->xAdvance);
        }
    }
}