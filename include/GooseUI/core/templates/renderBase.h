#ifndef _GOOSEUI_RENDERBASE_H_
#define _GOOSEUI_RENDERBASE_H_

namespace goose
{
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

                    virtual void beginFrame(int windowWidth, int windowHeight, color bgColor) = 0;
                    virtual void endFrame() = 0;

                    virtual void drawRect(float X, float Y, float W, float H, const color& C) = 0;
                };
            }
        }
    }
}

#endif /*_GOOSEUI_RENDERBASE_H_*/