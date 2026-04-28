#ifndef _GOOSEUI_FONTCFG_H_
#define _GOOSEUI_FONTCFG_H_

#include <string>

namespace GooseUI
{
    namespace font
    {
        namespace cfg
        {   
            struct bitmap
            {
                bool createMipmaps = false;   // Should we use the multi-bitmap scale method
                int mipmap_amount = 0;     // How many bitmap to make for this font? - Only create larger ones
                int mipmap_sizeRatio = 1;        // How much should each bitmap scale? - Add to scale factor
            };
            
            struct SDF
            {
                bool enableMsdf = true;         // Enable Multi-channel SDF
                int pixelRange = 4;             // Distance of glyph edge to edge of texture (pixels)
                int upsacleRes = 32;            // Resolution for a single texture glyph
            };
        }
        
        enum class type
        {
            bitmap,
            SDF
        };
        
        struct fontData
        {
            std::string PathToFont = "";
            int size = 0;
            
            type fontType = type::bitmap;
            union{ cfg::bitmap bitmapCfg; cfg::SDF sdfCfg; } advanceConfiguration;
        };
    }
}

#endif /*_GOOSEUI_FONTCFG_H_*/