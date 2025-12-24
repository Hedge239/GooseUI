#ifndef _GOOSEUI_LAYOUTCALCULATOR_H_
#define _GOOSEUI_LAYOUTCALCULATOR_H_

#include "GooseUI/core/types.h"

namespace goose
{
    namespace graphics
    {
        namespace layout
        {
            class calculator
            {
                public:
                static void getInitalOffsets(int (&distanceArray)[4], int windowWidth, int windowHeight, int X, int Y, int Width, int Height);
                static void calculateLayout(core::types::componentScale scaleMode, int alignments, core::types::layoutRestraints sizeRestraints, int distanceArray[4], int windowWidth, int windowHeight, int& X, int& Y, int& Width, int& Height);
            };
        }
    }
}

#endif