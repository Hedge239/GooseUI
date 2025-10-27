#ifndef _GOOSEUI_LAYOUTCALCULATOR_H_
#define _GOOSEUI_LAYOUTCALCULATOR_H_

#include "GooseUI/core/enumerations.h"

namespace goose
{

    namespace graphics
    {
        namespace layout
        {
            struct sizeRestraints
            {
                int minWidth = -1;
                int minHeight = -1;
                int maxWidth = -1;
                int maxHeight = -1;
            };

            class calculator
            {
                public:
                static void getInitalOffsets(int (&distanceArray)[4], int windowWidth, int windowHeight, int X, int Y, int Width, int Height);
                static void calculateLayout(core::enumerations::componentScale scaleMode, int alignments, sizeRestraints sizeRestraints, int distanceArray[4], int windowWidth, int windowHeight, int& X, int& Y, int& Width, int& Height);
            };
        }
    }
}

#endif