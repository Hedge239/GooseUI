#include "GooseUI/platform/xorg/widgets/xorg_button.h"
#include "GooseUI/platform/xorg/widgets/xorg_window.h"

#include <GooseUI/core/eventDispatcher.h>


namespace goose::platform::gXOrg
{
    gXOrg_button::gXOrg_button(widget::window* window, int eventID, core::eventDispatcher& evtDispatcher, core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int width, int height)
    :   _evtDispatcher(evtDispatcher), _eventID(eventID), _scaleing(componentScaleing), _alignment(componentAlign)
    {
        _host = dynamic_cast<gXOrg_window*>(window);
        _window = XCreateSimpleWindow(
            _host->getDisplay(),
            _host->getWindow(),
            X,
            Y,
            width,
            height,
            1,
            BlackPixel(_host->getDisplay(), DefaultScreen(_host->getDisplay())),
            0xCCCCCC
        );

        XSelectInput(_host->getDisplay(), _window, ExposureMask | ButtonPressMask);
        XMapWindow(_host->getDisplay(), _window); // Uh, it works.. I guess?

        _host->addToXEventLoop(this);
    }

    // WIDGET SETTINGS
    void gXOrg_button::setSize(int width, int height) {}
    void gXOrg_button::setPosistion(int X, int Y) {}
    void gXOrg_button::setLabel(std::string label) {}
    void gXOrg_button::setVisibility(bool isVisible) { if(!isVisible) {XUnmapWindow(_host->getDisplay(), _window);} else {XMapWindow(_host->getDisplay(), _window);} }

    // WIDGET MANAGEMENT
    void gXOrg_button::updateEdgeOffsets() {}

    void gXOrg_button::onClick() 
    {
        //zCore::zEvent evt{zCore::zEventType::ButtonPress, nullptr};
        core::event::event evt;
        _evtDispatcher.dispatch(_eventID, evt);
    }

    bool gXOrg_button::handelEvent(void* evtMsg) 
    {
        XEvent* event = static_cast<XEvent*>(evtMsg); // Sacrafice Safety for my sanity, is good
        if(event->type == ButtonPress && event->xany.window == _window)
        {
            this->onClick();
            return true;
        }

        return false;
    }

    // WIDGET RETURNS
    int gXOrg_button::getX() { return 0; }
    int gXOrg_button::getY() { return 0; }
    int gXOrg_button::getWidth() { return 0; }
    int gXOrg_button::getHeight() { return 0; }

    int gXOrg_button::getEventID() { return _eventID; }
}
