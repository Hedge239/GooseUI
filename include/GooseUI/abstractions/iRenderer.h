#ifndef _GOOSEUI_IRENDERER_H_
#define _GOOSEUI_IRENDERER_H_

#include "GooseUI/types.h"

namespace GooseUI
{
    namespace absractions
    {
        class iRenderer
        {
            public:
            virtual ~iRenderer() = default;
            
            virtual void initRenderer() = 0;
            
            virtual void beginFrame(int windowWidth, int windowHeight, const color &C) = 0;
            virtual void endFrame() = 0;
            
            virtual void drawRect(float X, float Y, float W, float H, const color &C) = 0;
            virtual void drawTexture() = 0;
            virtual void drawBitmapFont(unsigned int ID, float X, float Y, float W, float H, float u0, float u1, float v0, float v1, const color& color) = 0;
            virtual void drawSdfFont() = 0;
        };
    }
}

#endif /*_GOOSEUI_IRENDERER_H_*/