#ifndef _GOOSEUI_RENDERBASE_H_
#define _GOOSEUI_RENDERBASE_H_

#include "GooseUI/graphics/font/fontAtlas.h"

namespace goose
{
    namespace graphics
    {
        namespace font
        {
            class atlas; // FORWARD DECLERATION
        }
    }

    namespace core 
    {
        namespace templates
        {
            namespace renderBase
            {
                struct color { float R, G, B, A; };

                class renderer
                {
                    public:
                    virtual ~renderer() = default;

                    virtual void uploadFontAtlas(goose::graphics::font::atlas& atlas) = 0;

                    virtual void beginFrame(int windowWidth, int windowHeight, color bgColor) = 0;
                    virtual void endFrame() = 0;

                    // DrawCalls
                    virtual void drawTextureQuad(unsigned int ID, float X, float Y, float W, float H, float u0, float u1, float v0, float v1, const color& C) = 0;
                    virtual void drawRect(float X, float Y, float W, float H, const color& C) = 0;
                };
            }
        }
    }
}

#endif /*_GOOSEUI_RENDERBASE_H_*/