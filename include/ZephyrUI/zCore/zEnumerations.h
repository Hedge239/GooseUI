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
                DOES_SCALE,
                LOCK_TO_TOP,
                LOCK_TO_BOTTOM,
                LOCK_TO_LEFT,
                LOCK_TO_RIGHT
            };

            enum zEventType
            {
                BUTTON_PRESS
            };
        }
    }
}

#endif /*_ZENUMERATIONS_H_*/