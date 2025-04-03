#include "ZephyrUI/zPlatform/win32/zWin32.h"

// Normally this would be a bad idea, but since I know there are only 4 ints and the user shouldent touch this. Were fine... for now
// Summery for my friends - the useage of this variable to contained making it unlikely to have issues (But I know you will break it!)
int* zUI::zPlatform::zWin32::zWin32_WidgetAPI::getDistanceFromWindowEdges(HWND hwnd)
{
    static int distances[4];

    RECT currentBounds, windowBounds;
    GetClientRect(GetParent(hwnd), &windowBounds);
    GetWindowRect(hwnd, &currentBounds);

    MapWindowPoints(HWND_DESKTOP, GetParent(hwnd), (POINT*)&currentBounds, 2);

    // Right
    distances[0] = windowBounds.right - currentBounds.right;
    if(distances[0] < 0) {distances[0] = -distances[0];}

    // Left
    distances[1] = windowBounds.left - currentBounds.left;
    if(distances[1] < 0) {distances[1] = -distances[1];}

    // Top
    distances[2] = windowBounds.top - currentBounds.top;
    if(distances[2] < 0) {distances[2] = -distances[2];}

    // Bottom
    distances[3] = windowBounds.bottom - currentBounds.bottom;
    if(distances[3] < 0) {distances[3] = -distances[3];}

    return distances;
}

RECT zUI::zPlatform::zWin32::zWin32_WidgetAPI::calculateScaleAndSize(zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, int initalDistance[4], HWND hwnd)
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

    // Determine scaling
    bool doVerticalScale, doHorizontalScale;

    if(zComponentScale & zCore::zEnumerations::SCALE_HORIZONTAL) {doHorizontalScale = true;}
    if(zComponentScale & zCore::zEnumerations::SCALE_VERTICAL) {doVerticalScale = true;}
    if(zComponentScale & zCore::zEnumerations::SCALE_ALL) {doVerticalScale = true; doHorizontalScale = true;}

    // With Scale - Left/Right/Top/Bottem
    if((zComponentAlign & zCore::zEnumerations::ALIGN_LEFT) && (zComponentAlign & zCore::zEnumerations::ALIGN_RIGHT) && doHorizontalScale)
    {
        // Left/Right
        adjustedBounds.right = windowBounds.right - initalDistance[0];
    }

    if((zComponentAlign & zCore::zEnumerations::ALIGN_BOTTOM) && (zComponentAlign & zCore::zEnumerations::ALIGN_TOP) && doVerticalScale)
    {
        // Top/Bottom
        adjustedBounds.bottom = windowBounds.bottom - initalDistance[3];
    }


    // No Scale - Left/Right
    if((zComponentAlign & zCore::zEnumerations::ALIGN_RIGHT) && !(zComponentAlign & zCore::zEnumerations::ALIGN_LEFT) && !doHorizontalScale)
    {
        // Right
        adjustedBounds.left = windowBounds.right - widgetWidth - initalDistance[0];
        adjustedBounds.right = adjustedBounds.left + widgetWidth;
    }

    if((zComponentAlign & zCore::zEnumerations::ALIGN_RIGHT) && (zComponentAlign & zCore::zEnumerations::ALIGN_LEFT) && !doHorizontalScale)
    {
        // Left/Right
        adjustedBounds.left = windowBounds.left + initalDistance[1] + ((windowBounds.right - windowBounds.left - initalDistance[1] - initalDistance[0]) - widgetWidth) / 2;
        adjustedBounds.right = adjustedBounds.left + widgetWidth;
    }

    // No Scale - Top/Bottom
    if((zComponentAlign & zCore::zEnumerations::ALIGN_BOTTOM) && !(zComponentAlign & zCore::zEnumerations::ALIGN_TOP) && !doVerticalScale)
    {
        // Bottom
        adjustedBounds.top = windowBounds.bottom - widgetHeight - initalDistance[3];
        adjustedBounds.bottom = adjustedBounds.top + widgetHeight;
    }

    if((zComponentAlign & zCore::zEnumerations::ALIGN_BOTTOM) && (zComponentAlign & zCore::zEnumerations::ALIGN_TOP) && !doVerticalScale)
    {
        // Top/Bottom
        adjustedBounds.top = windowBounds.top + initalDistance[2] + ((windowBounds.bottom - windowBounds.top - initalDistance[2] - initalDistance[3]) - widgetHeight) / 2;
        adjustedBounds.bottom = adjustedBounds.top + widgetHeight;
    }


    // Debugging 

    /*
    std::cout << "-------- Math --------" << std::endl;
    std::cout << "Width: " << widgetWidth << std::endl;
    std::cout << "Height: " << widgetHeight << std::endl;
    std::cout << "DistanceToRight: " << initalDistance[0] << std::endl;
    std::cout << "DistanceToLeft: " << initalDistance[1] << std::endl;
    std::cout << "DistanceToBottom: " << initalDistance[2] << std::endl;
    std::cout << "DistanceToTop:" << initalDistance[3] << std::endl;
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