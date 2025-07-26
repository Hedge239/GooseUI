#ifndef _GOOSEUI_WIN32_SCALECALCULATOR_H_
#define _GOOSEUI_WIN32_SCALECALCULATOR_H_

#include "GooseUI/core/enumerations.h"

#include <windows.h>

namespace goose
{
    namespace platform
    {
        namespace gWin32
        {
            class gWin32_scaleCalculator
            {
                public:
                static RECT calculateScaleAndSize(core::enumerations::componentScale componentScale, int componentAlign, int initalDistance[4], HWND hwnd);
                static int* getDistanceFromWindowEdges(HWND hwnd);
            };
        }
    }
}

#endif /*_GOOSEUI_WIN32_SCALECALCULATOR_H_*/