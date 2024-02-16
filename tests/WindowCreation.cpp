#include "ZephyrUI/zWindow.h"
#include <iostream>

int main()
{
    zephyr::zWindowConfig TestWindow;
    TestWindow.className = "window1";
    TestWindow.displayTitle = "window1";

    zephyr::CreateWindow(TestWindow);

    zephyr::zWindowConfig TestWindow2;
    TestWindow2.className = "Window2";
    TestWindow2.displayTitle = "Window2";
    TestWindow2.displayWidth = 800;
    TestWindow2.displayHeight = 800;
    TestWindow2.disableResize = true;
    TestWindow2.disableMinimizeToggle = true;

    zephyr::CreateWindow(TestWindow2);
    zephyr::CloseWindow("Window1");

    zephyr::zWindowConfig TestWindow3;
    TestWindow3.className = "Window3";
    TestWindow3.displayTitle = "Window3"; 
    TestWindow3.disableToolBar = true;

    zephyr::CreateWindow(TestWindow3);
}