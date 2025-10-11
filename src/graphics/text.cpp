#include "GooseUI/graphics/text.h"
#include "GooseUI/graphics/font/fontLayout.h"
#include "GooseUI/graphics/font/font.h"

#include "GooseUI/core/templates/renderBase.h"


namespace goose::graphics
{
    void text::draw(core::templates::renderBase::renderer& renderer, graphics::font::font* font, const std::string& text, int X, int Y, const core::templates::renderBase::color& color)
    {
        font::atlas& atlas = *font->getAtlas();
        renderer.uploadFontAtlas(atlas);

        font::layout layout;
        layout.setText(text, font);

        for(const auto& gp : layout.getGlyphs())
        {
            if (gp.glyph->width == 0 || gp.glyph->height == 0) { continue; }

            float u0 = gp.glyph->u0;
            float v0 = gp.glyph->v0;
            float u1 = gp.glyph->u1;
            float v1 = gp.glyph->v1;

            v0 = 1.0f - v0;
            v1 = 1.0f - v1;
            std::swap(v0, v1);

            float xpos = X + gp.glyph->xOffset;
            float ypos = Y - (gp.glyph->height - gp.glyph->yOffset);
            float w = gp.glyph->width;
            float h = gp.glyph->height;

            //renderer.drawTextureQuad(atlas.getID(), X, Y, gp.glyph->width, gp.glyph->height, gp.glyph->u0, gp.glyph->u1, gp.glyph->v0, gp.glyph->v1, color);
            renderer.drawTextureQuad(atlas.getID(), X, Y, gp.glyph->width, gp.glyph->height, u0, v0, u1, v1, color);

            X += (gp.glyph->xAdvance);
        }
    }
}