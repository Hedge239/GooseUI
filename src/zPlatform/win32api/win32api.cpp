#include "ZephyrUI/zPlatform/win32api/win32api.h"
#include <iostream>

RECT zUI::zPlatform::Win32API::WidgetAPI::calculateScaleAndSize(zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, HWND hwnd, LPARAM lParam)
{
    // Get Widget & Window Size
    RECT currentBounds, adjustedBounds, windowBounds;
    GetClientRect(GetParent(hwnd), &windowBounds);
    GetWindowRect(hwnd, &currentBounds);

    MapWindowPoints(HWND_DESKTOP, GetParent(hwnd), (POINT*)&currentBounds, 2);

    // Scale Manganagement

    // Pos Mangeagement
    if(zComponentAlign &zCore::zEnumerations::ALIGN_CENTER)
    {

    }else 
    {
        if(zComponentAlign & zCore::zEnumerations::ALIGN_RIGHT)
        {
            int distanceFromRight = currentBounds.right - windowBounds.right;

            adjustedBounds.left = LOWORD(lParam) - (currentBounds.right - currentBounds.left) - distanceFromRight;
            adjustedBounds.top = currentBounds.top;
            adjustedBounds.right = adjustedBounds.left + (currentBounds.right - currentBounds.left);
            adjustedBounds.bottom = adjustedBounds.top + (currentBounds.bottom - currentBounds.top);
        }
        else if(zComponentAlign & zCore::zEnumerations::ALIGN_LEFT)
        {
        }
    }
    
    std::cout << adjustedBounds.left << std::endl;
    
    return adjustedBounds;
}

