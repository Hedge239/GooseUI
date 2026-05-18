#include "GooseUI/graphics/text.h"

#include "GooseUI/abstractions/iFont.h"
#include "GooseUI/font/fontLayout.h"
#include "GooseUI/context.h"


namespace GooseUI::graphics // Private
{
    static void _uploadFontAtlas(font::atlas &atlas)
    {
        if(atlas.isUploaded()){ return; }
        unsigned int id = application::getRenderer()->uploadTexture(atlas.getPixels().data(), atlas.getWidth(), atlas.getHeight(), true, true);
        
        atlas.setid(id);
        atlas.uploaded();
    }
    
    void text::_drawSDF(absractions::iFont *font, const std::string &text, int X, int Y, float scale, const color &color)
    {
        
    }
    
    void text::_drawBitmap(absractions::iFont *font, const std::string &text, int X, int Y, float scale, const color &color)
    {
        font::atlas& atlas = *font->getAtlas();

        font::layout layout;
        layout.setText(text, font);

        _uploadFontAtlas(atlas);

        for(const font::glyphPos &glyphPos : layout.getGlyphs())
        {
            if (glyphPos.g->width == 0 || glyphPos.g->height == 0){ X += glyphPos.g->xAdvance * scale; continue; }
            application::getRenderer()->drawTexture(
                atlas.getId(), 
                X, Y + (glyphPos.g->yOffset * scale), 
                glyphPos.g->width * scale, -glyphPos.g->height * scale, 
                glyphPos.g->u0, glyphPos.g->u1, 
                glyphPos.g->v0, glyphPos.g->v1, 
                color
            );

            X += (glyphPos.g->xAdvance * scale) + scale;
        }
    }
}

namespace GooseUI::graphics // Public
{
    void text::draw(absractions::iFont *font, const std::string &text, int X, int Y, float scale, const color &color)
    {
        switch(font->getFontData().fontType) 
        {
            case font::type::SDF:
            {
                _drawSDF(font, text, X, Y, scale, color);
            }
            default: // Bitmap
            {
                _drawBitmap(font, text, X, Y, scale, color);
            }
        }
    }
    
    void text::getSize(absractions::iFont *font, const std::string &text, float scale, int &outWidth, int &outHeight)
    {
        font::layout layout;
        layout.setText(text, font);

        outHeight = 0;
        outWidth = 0;

        for(const font::glyphPos& glyphPos : layout.getGlyphs())
        {
            if(glyphPos.g->width == 0 || glyphPos.g->height == 0)
            {
                outWidth += glyphPos.g->xAdvance * scale;
            }else 
            {
                outWidth += (glyphPos.g->xAdvance * scale) + scale;
                if(glyphPos.g->height * scale > outHeight){ outHeight = glyphPos.g->height * scale; }
            }
        }
    }
}