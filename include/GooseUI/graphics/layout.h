#ifndef _GOOSEUI_LAYOUT_H_
#define _GOOSEUI_LAYOUT_H_

#include "GooseUI/types.h"

namespace GooseUI
{
    namespace graphics
    {
        class layout
        {
            public:
            static void getInitalOffsets(int (&distanceArray)[4], int windowWidth, int windowHeight, int X, int Y, int Width, int Height);
            
            static void calculateBitmapTextLayout(int widgetWidth, int widgetHeight, float& scale, int& textWidth, int& textHeight);
            static void calculateLayout(
                bool calulateWithPos,
                widgetScaleing scaleMode, int alignments, 
                layoutRestraints sizeRestraints, 
                int distanceArray[4], 
                int windowWidth, int windowHeight,
                int windowPosX, int windowPosY,
                int& X, int& Y, 
                int& Width, int& Height
            );
        };
    }
}

#endif /*_GOOSEUI_LAYOUT_H_*/