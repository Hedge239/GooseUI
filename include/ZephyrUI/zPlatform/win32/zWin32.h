#ifndef _ZWIN32_H_
#define _ZWIN32_H_

#include "ZephyrUI/zCore/zEnumerations.h"
#include <Windows.h>

namespace zUI
{
    namespace zPlatform
    {
        namespace zWin32
        {
            class zWin32_WidgetAPI
            {
                public:
                static RECT calculateScaleAndSize(zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, int initalDistance[4], HWND hwnd);
                static int* getDistanceFromWindowEdges(HWND hwnd);
            };
        }
    }
}

#endif /*_ZWIN32_H_*/