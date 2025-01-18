#include "ZephyrUI/zPlatform/win32api/win32api.h"


RECT zUI::zPlatform::Win32API::WidgetAPI::calculateScaleAndSize(zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, HWND hwnd, LPARAM lParam)
{
    /*
        I Hate math,
        zComponentAlign is ment to be relative, meaning it will allways be the same distance from specified sides,
        zComponentScale is just there to determine weather it just moves or changes size to keep the distance,

        I been trying to find out this math for 2h 38m,
        I'm going to sleep on this tonight, and no matter what or how dirty it becomes IT WILL WORK!

        For now I will just pass the origional size through so it... works
    */

    RECT currentBounds, adjustedBounds;
    GetWindowRect(hwnd, &currentBounds);
    MapWindowPoints(HWND_DESKTOP, GetParent(hwnd), (POINT*)&currentBounds, 2);

    adjustedBounds = currentBounds;

    return adjustedBounds;
}

