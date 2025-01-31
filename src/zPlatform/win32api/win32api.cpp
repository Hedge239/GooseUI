#include "ZephyrUI/zPlatform/win32api/win32api.h"
#include <iostream>

// GLOBAL VARS //
int g_distanceFromRight;
int g_distanceFromLeft;
int g_distanceFromBottom;
int g_distanceFromTop;

RECT zUI::zPlatform::Win32API::WidgetAPI::calculateScaleAndSize(zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, HWND hwnd)
{
    // Get Widget & Window Size
    RECT currentBounds, adjustedBounds, windowBounds;
    GetClientRect(GetParent(hwnd), &windowBounds);
    GetWindowRect(hwnd, &currentBounds);

    MapWindowPoints(HWND_DESKTOP, GetParent(hwnd), (POINT*)&currentBounds, 2);

    adjustedBounds = currentBounds;
    
    // Get the widget Size
    int widgetWidth = currentBounds.right - currentBounds.left;
    int widgetHeight = currentBounds.bottom - currentBounds.top;

    // Set inital distances
    if(g_distanceFromRight == 0 )
    {
        g_distanceFromRight = windowBounds.right - currentBounds.right;
        if(g_distanceFromRight < 0) {g_distanceFromRight = -g_distanceFromRight;}
    }

    if(g_distanceFromLeft == 0 )
    {
        g_distanceFromLeft = windowBounds.left - currentBounds.left;
        if(g_distanceFromLeft < 0) {g_distanceFromLeft = -g_distanceFromLeft;}
    }

    if(g_distanceFromBottom == 0)
    {
        g_distanceFromBottom = windowBounds.bottom - currentBounds.bottom;
        if(g_distanceFromBottom < 0) {g_distanceFromBottom = -g_distanceFromBottom;}
    }

    if(g_distanceFromTop == 0)
    {
        g_distanceFromTop = windowBounds.top - currentBounds.top;
        if(g_distanceFromTop < 0) {g_distanceFromTop = -g_distanceFromTop;}
    }
    
    // Determine scaling
    bool doVerticalScale, doHorizontalScale;

    if(zComponentScale & zCore::zEnumerations::SCALE_HORIZONTAL) {doHorizontalScale = true;}
    if(zComponentScale & zCore::zEnumerations::SCALE_VERTICAL) {doVerticalScale = true;}
    if(zComponentScale & zCore::zEnumerations::SCALE_ALL) {doVerticalScale = true; doHorizontalScale = true;}

    // With Scale - Left/Right/Top/Bottem
    if((zComponentAlign & zCore::zEnumerations::ALIGN_LEFT) && (zComponentAlign & zCore::zEnumerations::ALIGN_RIGHT) && doHorizontalScale)
    {
        // Left/Right
        adjustedBounds.right = windowBounds.right - g_distanceFromRight;
    }

    if((zComponentAlign & zCore::zEnumerations::ALIGN_BOTTOM) && (zComponentAlign & zCore::zEnumerations::ALIGN_TOP) && doVerticalScale)
    {
        // Top/Bottom
        adjustedBounds.bottom = windowBounds.bottom - g_distanceFromBottom;
    }


    // No Scale - Left/Right
    if((zComponentAlign & zCore::zEnumerations::ALIGN_RIGHT) && !(zComponentAlign & zCore::zEnumerations::ALIGN_LEFT) && !doHorizontalScale)
    {
        // Right
        adjustedBounds.left = windowBounds.right - widgetWidth - g_distanceFromRight;
        adjustedBounds.right = adjustedBounds.left + widgetWidth;
    }

    if((zComponentAlign & zCore::zEnumerations::ALIGN_RIGHT) && (zComponentAlign & zCore::zEnumerations::ALIGN_LEFT) && !doHorizontalScale)
    {
        // Left/Right
        adjustedBounds.left = windowBounds.left + g_distanceFromLeft + ((windowBounds.right - windowBounds.left - g_distanceFromLeft - g_distanceFromRight) - widgetWidth) / 2;
        adjustedBounds.right = adjustedBounds.left + widgetWidth;
    }

    // No Scale - Top/Bottom
    if((zComponentAlign & zCore::zEnumerations::ALIGN_BOTTOM) && !(zComponentAlign & zCore::zEnumerations::ALIGN_TOP) && !doVerticalScale)
    {
        // Bottom
        adjustedBounds.top = windowBounds.bottom - widgetHeight - g_distanceFromBottom;
        adjustedBounds.bottom = adjustedBounds.top + widgetHeight;
    }

    if((zComponentAlign & zCore::zEnumerations::ALIGN_BOTTOM) && (zComponentAlign & zCore::zEnumerations::ALIGN_TOP) && !doVerticalScale)
    {
        // Top/Bottom
        adjustedBounds.top = windowBounds.top + g_distanceFromTop + ((windowBounds.bottom - windowBounds.top - g_distanceFromTop - g_distanceFromBottom) - widgetHeight) / 2;
        adjustedBounds.bottom = adjustedBounds.top + widgetHeight;
    }


    // Debugging 
    /*
    std::cout << "-------- Math --------" << std::endl;
    std::cout << "Width: " << widgetWidth << std::endl;
    std::cout << "Height: " << widgetHeight << std::endl;
    std::cout << "DistanceToRight: " << g_distanceFromRight << std::endl;
    std::cout << "DistanceToLeft: " << g_distanceFromLeft << std::endl;
    std::cout << "DistanceToBottom: " << g_distanceFromBottom << std::endl;
    std::cout << "DistanceToTop:" << g_distanceFromTop << std::endl;
    std::cout << "-------- Widget --------" << std::endl;
    std::cout << "Left: " << adjustedBounds.left << std::endl;
    std::cout << "Top: " << adjustedBounds.top << std::endl;
    std::cout << "Right: " << adjustedBounds.right << std::endl;
    std::cout << "Bottom: " << adjustedBounds.bottom << std::endl;
    std::cout << "-------- Window --------" << std::endl;
    std::cout << "Right: " << windowBounds.right << std::endl;
    std::cout << "Bottom: " << windowBounds.bottom << std::endl;
    */

    return adjustedBounds;
}