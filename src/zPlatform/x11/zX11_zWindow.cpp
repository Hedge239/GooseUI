#include "ZephyrUI/zPlatform/x11/zX11_zWindow.h"
#include "ZephyrUI/zCore/zWidget.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <stdio.h>

using namespace zUI;
using namespace zPlatform;
using namespace zX11;

zX11_zWindow::zX11_zWindow(const std::string& title, zUI::zCore::zEnumerations::zWindowPos windowPos, int width, int height)
{
    _display = XOpenDisplay(nullptr);
    if(!_display){printf("[ZephyrUI] [ERROR] : Faild to open xDisplay");}   // Wow actually adding logging to a lib im working on, welp I prop do that for windows later, spoken on 5/12/25

    int defaultScreen = DefaultScreen(_display);
    Window rootWindow = RootWindow(_display, defaultScreen);

    // Calculate zWindowPos
    int screenWidth, screenHeight;
    screenWidth = DisplayWidth(_display, defaultScreen);
    screenHeight = DisplayHeight(_display, defaultScreen);

    int posX, posY;
    switch(windowPos)
    {
        case zUI::zCore::zEnumerations::SCREEN_TOP:
            posX = (screenWidth - width) / 2;
            break;
        case zUI::zCore::zEnumerations::SCREEN_BOTTOM:
            posX = (screenWidth - width) / 2;
            posY = screenHeight - height;
            break;
        case zUI::zCore::zEnumerations::SCREEN_LEFT:
            posY = (screenHeight - height) / 2;
            break;
        case zUI::zCore::zEnumerations::SCREEN_RIGHT:
            posX = screenWidth - width;
            posY = (screenHeight - height) / 2;
        case zUI::zCore::zEnumerations::SCREEN_TOP_LEFT:
            break;
        case zUI::zCore::zEnumerations::SCREEN_TOP_RIGHT:
            posX = screenWidth - width;
            break;
        case zUI::zCore::zEnumerations::SCREEN_BOTTOM_LEFT:
            posY = screenHeight - height;
            break;
        case zUI::zCore::zEnumerations::SCREEN_BOTTOM_RIGHT:
            posX = screenWidth - width;
            posY = screenHeight - height;
            break;
        case zUI::zCore::zEnumerations::SCREEN_CENTER:
            posX = (screenWidth - width) / 2;
            posY = (screenHeight - height) / 2;
            break;

        default:
            break;
    }

    // Create Window
    _window = XCreateSimpleWindow(
        _display,
        rootWindow,
        posX,
        posY,
        width,
        height,
        2,
        BlackPixel(_display, defaultScreen),
        WhitePixel(_display, defaultScreen)
    );

    // Set window defaults & inputEvents
    XSelectInput(_display, _window, ExposureMask | ButtonPressMask | StructureNotifyMask);
    XStoreName(_display, _window, title.c_str());
}

zX11_zWindow::~zX11_zWindow()
{
    XDestroyWindow(_display, _window);
    XCloseDisplay(_display);
}

// Window Settings
void zX11_zWindow::setTitle(const std::string& title) {}
void zX11_zWindow::setSize(int width, int height) {}

// Returns
Display* zX11_zWindow::getDisplay() {return _display;}
Window zX11_zWindow::getWindow() { return _window;}
int zX11_zWindow::getPosX() {return 0;}
int zX11_zWindow::getPosY() {return 0;}
int zX11_zWindow::getWidth() {return 0;}
int zX11_zWindow::getHeight() {return 0;}

// Window Management
void zX11_zWindow::show() 
{
    XMapWindow(_display, _window);
}

void zX11_zWindow::hide() {}
void zX11_zWindow::destroy() {}
void zX11_zWindow::draw() {}

void zX11_zWindow::addToEventLoop(zCore::zWidget* widget) {_childrenWidgets.push_back(widget);}

void zX11_zWindow::HandelEvents()
{
    while(true)
    {
        XEvent event;
        XNextEvent(_display, &event);
        
        // Passthrough to widgets
        for(auto& widget : _childrenWidgets)
        {
            if(widget->handelEvent(&event))
            break;
        }
    }
}