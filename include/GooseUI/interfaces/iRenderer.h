#ifndef _GOOSEUI_IRENDERER_H_
#define _GOOSEUI_IRENDERER_H_

#include "GooseUI/core/types.h"

namespace goose
{
    namespace graphics
    {
        namespace font
        {
            class atlas;    // FORWARD DECLERATION
        }
    }
    
    namespace interface
    {
        class iWidget;      // FORWARD DECLERATION
        
        class iRenderer
        {
            public:
            virtual ~iRenderer() = default;

            virtual void uploadFontAtlas(goose::graphics::font::atlas& atlas) = 0;

            virtual void beginFrame(int windowWidth, int windowHeight, const core::types::color& bgColor) = 0;
            virtual void endFrame() = 0;

            // DrawCalls
            virtual void drawTextureQuad(unsigned int ID, float X, float Y, float W, float H, float u0, float u1, float v0, float v1, const core::types::color& C) = 0;
            virtual void drawRect(float X, float Y, float W, float H, const core::types::color& C) = 0;
        };
    }
}

#endif /*_GOOSEUI_IRENDERER_H_*/