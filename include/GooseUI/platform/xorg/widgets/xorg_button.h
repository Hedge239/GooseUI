#ifndef _GOOSEUI_XORG_BUTTON_H_
#define _GOOSEUI_XORG_BUTTON_H_

#include "GooseUI/widgets/button.h"

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

namespace goose 
{
    namespace platform
    {
        namespace gXOrg
        {
            class gXOrg_window; // FORWARD DELCERATION

            class gXOrg_button : public widget::button
            {
                gXOrg_window* _host;
                Window _window;

                XftFont *_font;
                XftColor _fontColor;

                std::string _label;

                int _eventID;
                int _alignment;
                int _initalPos[4];

                core::enumerations::componentScale _scaleing;
                core::eventDispatcher& _evtDispatcher;

                public:
                gXOrg_button(widget::window* window, int eventID, core::eventDispatcher& evtDispatcher, core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int width, int height);

                // OVERIDES //
                bool handelEvent(void* evtMsg) override;

                void updateEdgeOffsets() override;
                void setSize(int Width, int Height) override;
                void setPosistion(int X, int Y) override;

                int getEventID() override;

                int getX() override;
                int getY() override;
                int getWidth() override;
                int getHeight() override;

                void onClick() override;

                void setVisibility(bool isVisible) override;
                void setLabel(std::string label) override;
            };
        }
    }
}

#endif /*_GOOSEUI_XORG_BUTTON_H_*/