#ifndef _GOOSEUI_LAYOUTCALCULATOR_H_
#define _GOOSEUI_LAYOUTCALCULATOR_H_

#include "GooseUI/core/enumerations.h"

namespace goose
{
    namespace graphics
    {
        class layoutCalculator
        {
            public:
            static void getInitalOffsets(int (&distanceArray)[4], int windowWidth, int windowHeight, int X, int Y, int Width, int Height);
            static void calculateLayout(core::enumerations::componentScale scaleMode, int alignments, int distanceArray[4], int windowWidth, int windowHeight, int& X, int& Y, int& Width, int& Height);
        };
    }
}

#endif