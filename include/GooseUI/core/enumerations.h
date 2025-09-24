#ifndef _GOOSEUI_ENUMERATIONS_H_
#define _GOOSEUI_ENUMERATIONS_H_

namespace goose
{
    namespace core 
    {
        namespace enumerations
        {
            enum windowPos
            {
                SCREEN_TOP,
                SCREEN_BOTTOM,
                SCREEN_LEFT,
                SCREEN_RIGHT,
                SCREEN_TOP_LEFT,
                SCREEN_TOP_RIGHT,
                SCREEN_BOTTOM_LEFT,
                SCREEN_BOTTOM_RIGHT,
                SCREEN_CENTER
            };

            enum componentScale
            {
                SCALE_NONE,
                SCALE_VERTICAL,
                SCALE_HORIZONTAL,
                SCALE_ALL
            };

            enum componentAlign
            {
                ALIGN_TOP = 1 << 0,
                ALIGN_BOTTOM = 1 << 1,
                ALIGN_LEFT = 1 << 2,
                ALIGN_RIGHT = 1 << 3
            };

            enum graphicsBackend
            {
                opengl,
                vulkan
            };
        }
    }
}

#endif /*_GOOSEUI_ENUMERATIONS_H_*/