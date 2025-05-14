#include "ZephyrUI/zPlatform/x11/zX11_zButton.h"
#include "ZephyrUI/zPlatform/x11/zX11_zWindow.h"

#include "ZephyrUI/zCore/zEventDispatcher.h"
#include <X11/Xlib.h>

using namespace zUI;
using namespace zPlatform;
using namespace zX11;


zX11_zButton::zX11_zButton(zUI::zWidget::zWindow* window, int eventID, zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, int X, int Y, int Width, int Height, zCore::zEventDispatcher& EvtDispatcher)
    :  _eventDispatcher(EvtDispatcher), _eventID(eventID), _scale(zComponentScale), _Alignment(zComponentAlign)
    {
        _host = dynamic_cast<zX11_zWindow*>(window);
        _window = XCreateSimpleWindow(
            _host->getDisplay(),
            _host->getWindow(),
            (400 - Width) / 2,
            (300 - Height) / 2,
            Width,
            Height,
            1,
            BlackPixel(_host->getDisplay(), DefaultScreen(_host->getDisplay())),
            0xCCCCCC
        );

        XSelectInput(_host->getDisplay(), _window, ExposureMask | ButtonPressMask);
        XMapWindow(_host->getDisplay(), _window); // Uh, it works.. I guess?
    }

// Window Settings
void zX11_zButton::updateEdgeOffsets() {}

void zX11_zButton::setPos(int X, int Y) {}
void zX11_zButton::setSize(int Width, int Height) {}
void zX11_zButton::setLabel(std::string text) {}

// Returns
int zX11_zButton::getEventID() {return 0;}
int zX11_zButton::getX() {return 0;}
int zX11_zButton::getY() {return 0;}
int zX11_zButton::getWidth() {return 0;}
int zX11_zButton::getHeight() {return 0;}

// Widget Management
void zX11_zButton::onClick()
{
    //zCore::zEvent evt{zCore::zEventType::ButtonPress, nullptr};
    zCore::zEvent evt;
    _eventDispatcher.dispatch(_eventID, evt);
}