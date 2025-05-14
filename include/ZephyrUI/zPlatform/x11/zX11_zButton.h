#ifndef _ZX11_ZBUTTON_H_
#define _ZX11_ZBUTTON_H_

#include "ZephyrUI/zWidget/zButton.h"
#include <X11/Xlib.h>

namespace zUI
{
    namespace zPlatform
    {
        namespace zX11
        {
            // FORWARD DECLERATION
            class zX11_zWindow;

            class zX11_zButton : public zWidget::zButton
            {
                zX11_zWindow* _host;
                Window _window;

                int _eventID; // Widget Identifier for events
                int _Alignment; // Widget Positioning
                int _initalPos[4]; // Inital distance from window edges
                zCore::zEnumerations::zComponentScale _scale; // Widget Scaling
                zCore::zEventDispatcher& _eventDispatcher;

                public:
                zX11_zButton(zUI::zWidget::zWindow* window, int eventID, zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, int X, int Y, int Width, int Height, zCore::zEventDispatcher& EvtDispatcher);

                // OVERIDES //
                void setPos(int X, int Y) override;
                void setSize(int Width, int Height) override;
                void updateEdgeOffsets() override;

                int getEventID() override;

                int getX() override;
                int getY() override;
                int getWidth() override;
                int getHeight() override;
                
                void onClick() override;
                void setLabel(std::string text) override;
            };
        }
    }
}

#endif /*_ZX11_ZBUTTON_H_*/