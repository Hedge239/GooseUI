#ifndef _GOOSEUI_FONT_H_
#define _GOOSEUI_FONT_H_

#include <string>

namespace GooseUI
{
    namespace font
    {
        enum class type
        {
            bitmap,
            SDF
        };
        
        struct fontCfg_bitmap
        {
            bool advanceScaleing = false;   // Should we use the multi-bitmap scale method
            int scale_bitmapAmount = 0;     // How many bitmap to make for this font? - Only create larger ones
            int scale_sizeRatio = 1;        // How much should each bitmap scale? - Add to scale factor
        };
        
        struct fontCfg_SDF
        {
            bool enableMsdf = true;         // Enable Multi-channel SDF
            int pixelRange = 4;             // Distance of glyph edge to edge of texture (pixels)
            int upsacleRes = 32;            // Resolution for a single texture glyph
        };
        
        struct font
        {
            std::string PathToFont = "";
            int initalSize = 0;
            
            type fontType = type::bitmap;
            union{ fontCfg_bitmap bitmapCfg; fontCfg_SDF sdfCfg; } advanceConfiguration;
        };
    }
}

#endif /*_GOOSEUI_FONT_H_*/