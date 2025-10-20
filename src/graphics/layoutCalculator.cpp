#include "GooseUI/graphics/layoutCalculator.h"

namespace goose::graphics
{
    void layoutCalculator::getInitalOffsets(int (&distanceArray)[4], int windowWidth, int windowHeight, int X, int Y, int Width, int Height)
    {
        distanceArray[0] = windowWidth - (X + Width); // RIGHT
        if(distanceArray[0] < 0) { distanceArray[0] = -distanceArray[0]; }

        distanceArray[1] = X; // LEFT
        if(distanceArray[1] < 0) { distanceArray[1] = -distanceArray[1]; }

        distanceArray[2] = windowHeight - (Y + Height); // BOTTOM
        if(distanceArray[2] < 0) { distanceArray[2] = -distanceArray[2]; }

        distanceArray[3] = Y; // TOP
        if(distanceArray[3] < 0) { distanceArray[3] = -distanceArray[3]; }
    }

    void layoutCalculator::calculateLayout(core::enumerations::componentScale scaleMode, int alignments, int distanceArray[4], int windowWidth, int windowHeight, int &X, int &Y, int &Width, int &Height)
    {
        // Determine scaleing
        bool doVerticalScaleing = false, doHorizontalScaleing = false;
        if(scaleMode & core::enumerations::SCALE_HORIZONTAL) { doHorizontalScaleing = true; }
        if(scaleMode & core::enumerations::SCALE_VERTICAL) { doVerticalScaleing = true; }
        if(scaleMode & core::enumerations::SCALE_ALL) { doHorizontalScaleing = true; doVerticalScaleing = true; }

        // With Scale - Left/Right/Top/Bottem
        if((alignments & core::enumerations::ALIGN_LEFT) && (alignments & core::enumerations::ALIGN_RIGHT) && doHorizontalScaleing) 
            { X = distanceArray[1]; Width  = windowWidth - distanceArray[1] - distanceArray[0]; }
        if((alignments & core::enumerations::ALIGN_BOTTOM) && (alignments & core::enumerations::ALIGN_TOP) && doVerticalScaleing)
            { Y = distanceArray[3]; Height = windowHeight - distanceArray[3] - distanceArray[2]; }

        // No Scale - Left/Right
        if((alignments & core::enumerations::ALIGN_RIGHT) && !(alignments & core::enumerations::ALIGN_LEFT) && !doHorizontalScaleing)
            { X = windowWidth - distanceArray[0] - Width; }
        if((alignments & core::enumerations::ALIGN_RIGHT) && (alignments & core::enumerations::ALIGN_LEFT) && !doHorizontalScaleing)
            { X = distanceArray[1] + ((windowWidth - distanceArray[1] - distanceArray[0] - Width) / 2); }

        // No Scale - Top/Bottom
        if((alignments & core::enumerations::ALIGN_BOTTOM) && !(alignments & core::enumerations::ALIGN_TOP) && !doVerticalScaleing)
            { Y = windowHeight - distanceArray[2] - Height; }
        if((alignments & core::enumerations::ALIGN_BOTTOM) && (alignments & core::enumerations::ALIGN_TOP) && !doVerticalScaleing)
            { Y = distanceArray[3] + ((windowHeight - distanceArray[3] - distanceArray[2] - Height) / 2); }

        // Clamps
        if(X <= 0) { X = 0; }
        if(Y <= 0) { Y = 0; }
        if(Width <= 0) { Width=0; }
        if(Height <= 0) { Height = 0; }
    }
}