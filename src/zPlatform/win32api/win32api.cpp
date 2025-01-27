#include "ZephyrUI/zPlatform/win32api/win32api.h"
#include <iostream>

// GLOBAL VARS //
int g_distanceFromRight;
int g_distanceFromBottom;

RECT zUI::zPlatform::Win32API::WidgetAPI::calculateScaleAndSize(zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, HWND hwnd)
{
    // Get Widget & Window Size
    RECT currentBounds, adjustedBounds, windowBounds;
    GetClientRect(GetParent(hwnd), &windowBounds);
    GetWindowRect(hwnd, &currentBounds);

    MapWindowPoints(HWND_DESKTOP, GetParent(hwnd), (POINT*)&currentBounds, 2);

    // Get Widget Size
    int widgetWidth = currentBounds.right - currentBounds.left;
    int widgetHeight = currentBounds.bottom - currentBounds.top;
    
    // Get Distance From Right & Bottom - If 0, not my problem
    if(g_distanceFromRight == 0 )
    {
        g_distanceFromRight = windowBounds.right - currentBounds.right;
        if(g_distanceFromRight < 0) {g_distanceFromRight = -g_distanceFromRight;}
    }

    if(g_distanceFromBottom == 0)
    {
        g_distanceFromBottom = windowBounds.bottom - currentBounds.bottom;
        if(g_distanceFromBottom < 0) {g_distanceFromBottom = -g_distanceFromBottom;}
    }

    // Scale Manganagement
    
    // Pos Mangeagement
    if(zComponentAlign &zCore::zEnumerations::ALIGN_CENTER)
    {

    }else 
    {
        if(zComponentAlign & zCore::zEnumerations::ALIGN_RIGHT)
        {
            adjustedBounds.left = windowBounds.right - widgetWidth - g_distanceFromRight;
            adjustedBounds.right = adjustedBounds.left + widgetWidth;
            adjustedBounds.top = currentBounds.top;
            adjustedBounds.bottom = adjustedBounds.top + widgetHeight;
        }
        else if(zComponentAlign & zCore::zEnumerations::ALIGN_LEFT)
        {
        }
    }

    std::cout << "-------- Math --------" << std::endl;
    std::cout << "Width: " << widgetWidth << std::endl;
    std::cout << "Height: " << widgetHeight << std::endl;
    std::cout << "DistanceToRight: " << g_distanceFromRight << std::endl;
    std::cout << "DistanceToBottom: " << g_distanceFromBottom << std::endl;
    std::cout << "-------- Widget --------" << std::endl;
    std::cout << "Left: " << adjustedBounds.left << std::endl;
    std::cout << "Top: " << adjustedBounds.top << std::endl;
    std::cout << "Right: " << adjustedBounds.right << std::endl;
    std::cout << "Bottom: " << adjustedBounds.bottom << std::endl;
    std::cout << "-------- Window --------" << std::endl;
    std::cout << "Right: " << windowBounds.right << std::endl;
    std::cout << "Bottom: " << windowBounds.bottom << std::endl;

    return adjustedBounds;
}

