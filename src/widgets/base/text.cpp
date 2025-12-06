#include "GooseUI/widgets/base/text.h"

#include "GooseUI/graphics/font/fontLayout.h"
#include "GooseUI/graphics/font/font.h"

#include "GooseUI/core/templates/renderBase.h"


namespace goose::widgets::base
{
    void text::draw(core::templates::renderBase::renderer& renderer, graphics::font::font* font, const std::string& text, int X, int Y, int scale, const core::templates::renderBase::color& color)
    {
        graphics::font::atlas& atlas = *font->getAtlas();
        renderer.uploadFontAtlas(atlas);

        graphics::font::layout layout;
        layout.setText(text, font);

        for(const graphics::font::glyphPos& gp : layout.getGlyphs())
        {
            if (gp.glyph->width == 0 || gp.glyph->height == 0) { X += gp.glyph->xAdvance * scale; continue; }
            renderer.drawTextureQuad(
                atlas.getID(), 
                X, Y + (gp.glyph->yOffset * scale), 
                gp.glyph->width * scale, -gp.glyph->height * scale, 
                gp.glyph->u0, gp.glyph->u1, 
                gp.glyph->v0, gp.glyph->v1, 
                color
            );

            X += (gp.glyph->xAdvance * scale) + scale;
        }
    }
    
    void text::getSize(graphics::font::font *font, const std::string &text, int scale, int &outWidth, int &outHeight)
    {
        graphics::font::layout layout;
        layout.setText(text, font);
        
        outHeight = 0;
        outWidth = 0;
        
        for(const graphics::font::glyphPos& gp : layout.getGlyphs())
        {
            if(gp.glyph->width == 0 || gp.glyph->height == 0)
            {
                outWidth += gp.glyph->xAdvance * scale;
            }else 
            {
                outWidth += (gp.glyph->xAdvance * scale) + scale;
                if(gp.glyph->height * scale > outHeight){ outHeight = gp.glyph->height * scale; }
            }
        }
    }
}