#include "GooseUI/platform/xorg/widgets/xorg_window.h"
#include "GooseUI/widgets/widget_base.h"

#include <stdio.h>

#include <X11/Xutil.h>
#include <X11/Xatom.h>


namespace goose::platform::gXOrg
{
    gXOrg_window::gXOrg_window(const std::string& title, goose::core::enumerations::windowPos posistion, int width, int height)
    {
        _display = XOpenDisplay(nullptr);
        if(!_display) { printf("[GooseUI] -- Faild to open xDisplay\n"); } // Wow actual debugging

        int defaultScreen = DefaultScreen(_display);
        Window rootWindow = RootWindow(_display, defaultScreen);

        // Calculate windowPos
        int screenWidth, screenHeight;
        screenWidth = DisplayWidth(_display, defaultScreen);
        screenHeight = DisplayHeight(_display, defaultScreen);

        int posX, posY;
        switch(posistion)
        {
            case goose::core::enumerations::SCREEN_TOP:
                posX = (screenWidth - width) / 2;
                break;
            case goose::core::enumerations::SCREEN_BOTTOM:
                posX = (screenWidth - width) / 2;
                posY = screenHeight - height;
                break;
            case goose::core::enumerations::SCREEN_LEFT:
                posY = (screenHeight - height) / 2;
                break;
            case goose::core::enumerations::SCREEN_RIGHT:
                posX = screenWidth - width;
                posY = (screenHeight - height) / 2;
                break;
            case goose::core::enumerations::SCREEN_TOP_LEFT:
                break;
            case goose::core::enumerations::SCREEN_TOP_RIGHT:
                posX = screenWidth - width;
                break;
            case goose::core::enumerations::SCREEN_BOTTOM_LEFT:
                posY = screenHeight - height;
                break;
            case goose::core::enumerations::SCREEN_BOTTOM_RIGHT:
                posX = screenWidth - width;
                posY = screenHeight - height;
                break;
            case goose::core::enumerations::SCREEN_CENTER:
                posX = (screenWidth - width) / 2;
                posY = (screenHeight - height) / 2;
                break;

            default:
                break;
        }

        // Create the Window
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

        // Give title & enable inputEvents
        XSelectInput(_display, _window, ExposureMask | ButtonPressMask | StructureNotifyMask);
        XStoreName(_display, _window, title.c_str());
    }

    gXOrg_window::~gXOrg_window()
    {
        XDestroyWindow(_display, _window);
        XCloseDisplay(_display);
    }
    
    // WINDOW SETTINGS
    void gXOrg_window::setHeader(const std::string& title, bool isVisible, bool hasButtons, bool hasMinimize, bool hasMaximise)
    {
        if(!title.empty()) { XStoreName(_display, _window, title.c_str()); }

        // PAIN
        struct { long flags, functions, decorations, inputMode, status; } hints = {0};

        if(!isVisible)
        {
            hints.flags = 1L << 1 | 1L << 0;

            Atom motif = XInternAtom(_display, "_MOTIF_WM_HINTS", false);
            XChangeProperty(_display, _window, motif, motif, 32, PropModeReplace, reinterpret_cast<unsigned char*>(&hints), 5);
        }else 
        {
            XDeleteProperty(_display, _window, XInternAtom(_display, "_MOTIF_WM_HINTS", False));
        }

        if(hasMaximise) { this->isResizeable(false); } else { this->isResizeable(true); }   // ugh

        if(!hasMinimize) { printf("[GooseUI] -- Variable [hasMinimize] is unsuported for [xOrg]\n"); }
        if(!hasMinimize) { printf("[GooseUI] -- Variable [hasButtons] is unsuported for [xOrg]\n"); }

        XFlush(_display);
    }

    void gXOrg_window::setSize(int width, int height)
    {
        XSizeHints sizeHints;
        sizeHints.flags = PSize;
        sizeHints.width = width;
        sizeHints.height = height;

        XSetNormalHints(_display, _window, &sizeHints);
        XResizeWindow(_display, _window, width, height);
        XFlush(_display);
    }

    void gXOrg_window::isResizeable(bool isResizeable)
    {
        XSizeHints* sizeHints = XAllocSizeHints();

        if(!isResizeable)
        {
            sizeHints->flags = PMinSize | PMaxSize;
            sizeHints->min_width = sizeHints->max_width = getWidth();
            sizeHints->min_height = sizeHints->max_height = getHeight();
        }else 
        {
            long currentHints;
            XGetWMNormalHints(_display, _window, sizeHints, &currentHints);
            sizeHints->flags &= ~(PMinSize | PMaxSize);
        }

        XSetWMNormalHints(_display, _window, sizeHints);
        XFree(sizeHints);
    }

    void gXOrg_window::isAllwaysOnTop(bool isOnTop) { printf("[GooseUI] -- Variable [isOnTop] is unsuported for [xOrg]\n"); }

    // WINDOW MANAGEMENT
    void gXOrg_window::maximize() 
    {
        Atom wmState = XInternAtom(_display, "_NET_WM_STATE", false);
        Atom maxWidth = XInternAtom(_display, "_NET_WM_STATE_MAXIMIZED_HORZ", false);
        Atom maxHeight = XInternAtom(_display, "_NET_WM_STATE_MAXIMIZED_VERT", false);

        XEvent event;
        event.xclient.type = ClientMessage;
        event.xclient.window = _window;
        event.xclient.message_type = wmState;
        event.xclient.format = 32;
        event.xclient.data.l[0] = 1;
        event.xclient.data.l[1] = maxWidth;
        event.xclient.data.l[2] = maxHeight;

        XSendEvent(_display, DefaultRootWindow(_display), false, SubstructureNotifyMask, &event);
    }

    void gXOrg_window::minimize() { XIconifyWindow(_display, _window, DefaultScreen(_display)); XFlush(_display); }

    void gXOrg_window::restoreSize() 
    {
        Atom wmState = XInternAtom(_display, "_NET_WM_STATE", false);
        Atom maxWidth = XInternAtom(_display, "_NET_WM_STATE_MAXIMIZED_HORZ", false);
        Atom maxHeight = XInternAtom(_display, "_NET_WM_STATE_MAXIMIZED_VERT", false);

        XEvent event;
        event.xclient.type = ClientMessage;
        event.xclient.window = _window;
        event.xclient.message_type = wmState;
        event.xclient.format = 32;
        event.xclient.data.l[0] = 0;
        event.xclient.data.l[1] = maxWidth;
        event.xclient.data.l[2] = maxHeight;

        XSendEvent(_display, DefaultRootWindow(_display), false, SubstructureNotifyMask, &event);
    }

    void gXOrg_window::show() { XMapWindow(_display, _window); XFlush(_display); }
    void gXOrg_window::hide() { XUnmapWindow(_display, _window); XFlush(_display); }

    void gXOrg_window::destroy() { XDestroyWindow(_display, _window); }

    void gXOrg_window::addToXEventLoop(widget::widget_base* widget) { _children.push_back(widget); }
    void gXOrg_window::handelEvents()
    {
        while(true)
        {
            XEvent event;
            XNextEvent(_display, &event);

            for(auto& widget_base : _children)
            {
                if(widget_base->handelEvent(&event))
                break;
            }
        }
    }

    // RETURNS
    Display* gXOrg_window::getDisplay() { return _display; }
    Window gXOrg_window::getWindow() { return _window; }

    int gXOrg_window::getWidth() { XWindowAttributes windowAtr; XGetWindowAttributes(_display, _window, &windowAtr); return windowAtr.width; }
    int gXOrg_window::getHeight() { XWindowAttributes windowAtr; XGetWindowAttributes(_display, _window, &windowAtr); return windowAtr.height; }
}