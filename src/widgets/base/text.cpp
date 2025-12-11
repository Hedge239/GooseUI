#include "GooseUI/widgets/base/text.h"

#include "GooseUI/graphics/font/fontLayout.h"
#include "GooseUI/graphics/font/font.h"

#include "GooseUI/core/templates/renderBase.h"


namespace goose::widgets::base
{
    void text::draw(core::templates::renderBase::renderer& renderer, graphics::font::font* font, const std::string& text, int X, int Y, float scale, const core::templates::renderBase::color& color)
    {
        graphics::font::atlas& atlas = *font->getAtlas();
        renderer.uploadFontAtlas(atlas);

        graphics::font::layout layout;
        layout.setText(text, font);

        for(const graphics::font::glyphPos& gp : layout.getGlyphs())
        {
            if (gp.g->width == 0 || gp.g->height == 0) { X += gp.g->xAdvance * scale; continue; }
            renderer.drawTextureQuad(
                atlas.getID(), 
                X, Y + (gp.g->yOffset * scale), 
                gp.g->width * scale, -gp.g->height * scale, 
                gp.g->u0, gp.g->u1, 
                gp.g->v0, gp.g->v1, 
                color
            );

            X += (gp.g->xAdvance * scale) + scale;
        }
    }
    
    void text::getSize(graphics::font::font *font, const std::string &text, float scale, int &outWidth, int &outHeight)
    {
        graphics::font::layout layout;
        layout.setText(text, font);
        
        outHeight = 0;
        outWidth = 0;
        
        for(const graphics::font::glyphPos& gp : layout.getGlyphs())
        {
            if(gp.g->width == 0 || gp.g->height == 0)
            {
                outWidth += gp.g->xAdvance * scale;
            }else 
            {
                outWidth += (gp.g->xAdvance * scale) + scale;
                if(gp.g->height * scale > outHeight){ outHeight = gp.g->height * scale; }
            }
        }
    }
}