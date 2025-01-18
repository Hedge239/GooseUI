#ifndef _ZENUMERATIONS_H_
#define _ZENUMERATIONS_H_

namespace zUI
{
    namespace zCore
    {
        namespace zEnumerations
        {
            enum zWindowPos
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

            enum zComponentScale
            {
                SCALE_NONE,
                SCALE_VERTICAL,
                SCALE_HORIZONTAL,
                SCALE_ALL
            };

            enum zComponentAlign
            {
                ALIGN_TOP = 1 << 0,
                ALIGN_BOTTOM = 1 << 1,
                ALIGN_LEFT = 1 << 2,
                ALIGN_RIGHT = 1 << 3,
                ALIGN_CENTER = 1 << 4
            };
        }
    }
}

#endif /*_ZENUMERATIONS_H_*/