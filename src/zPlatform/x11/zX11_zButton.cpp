#include "ZephyrUI/zPlatform/x11/zX11_zButton.h"
#include "ZephyrUI/zPlatform/x11/zX11_zWindow.h"

#include "ZephyrUI/zCore/zEventDispatcher.h"

#include <X11/X.h>
#include <X11/Xlib.h>

using namespace zUI;
using namespace zPlatform;
using namespace zX11;


zX11_zButton::zX11_zButton(zUI::zWidget::zWindow* window, int eventID, zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, int X, int Y, int Width, int Height, zCore::zEventDispatcher& EvtDispatcher)
    :  _eventDispatcher(EvtDispatcher), _eventID(eventID), _scale(zComponentScale), _Alignment(zComponentAlign), _X(X), _Y(Y), _width(Width), _height(Height)
    {
        _host = dynamic_cast<zX11_zWindow*>(window);
        _window = XCreateSimpleWindow(
            _host->getDisplay(),
            _host->getWindow(),
            _X,
            _Y,
            Width,
            Height,
            1,
            BlackPixel(_host->getDisplay(), DefaultScreen(_host->getDisplay())),
            0xCCCCCC
        );

        XSelectInput(_host->getDisplay(), _window, ExposureMask | ButtonPressMask);
        XMapWindow(_host->getDisplay(), _window); // Uh, it works.. I guess?

        _host->addToEventLoop(this);
    }

// Window Settings
void zX11_zButton::updateEdgeOffsets() {}

void zX11_zButton::setPos(int X, int Y) {}
void zX11_zButton::setSize(int Width, int Height) {}
void zX11_zButton::setLabel(std::string text) {}

// Returns
int zX11_zButton::getEventID() {return _eventID;}
int zX11_zButton::getX() {return _X;}
int zX11_zButton::getY() {return _Y;}
int zX11_zButton::getWidth() {return _width;}
int zX11_zButton::getHeight() {return _height;}

// Widget Management
bool zX11_zButton::handelEvent(void* eventMsg)
{
    XEvent* event = static_cast<XEvent*>(eventMsg); // Sacrafice Safety for my sanity, is good

    if(event->type == ButtonPress)
    {
        // Dang it was this easy
        if(event->xany.window == _window)
        {
            this->onClick();
            return True;
        }
    }

    return false;
}

void zX11_zButton::onClick()
{
    //zCore::zEvent evt{zCore::zEventType::ButtonPress, nullptr};
    zCore::zEvent evt;
    _eventDispatcher.dispatch(_eventID, evt);
}