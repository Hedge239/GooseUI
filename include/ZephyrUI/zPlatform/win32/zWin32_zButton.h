#ifndef _ZWIN32_ZBUTTON_H_
#define _ZWIN32_ZBUTTON_H_

#include "ZephyrUI/zWidget/zButton.h"
#include <windows.h>

namespace zUI
{
    namespace zPlatform
    {
        namespace zWin32
        {
            // FORWARD DECLERATION
            class zWin32_zWindow;

            class zWin32_zButton : public zWidget::zButton
            {
                HWND _hwnd;
                static WNDPROC _OrgProc; 
                zWin32_zWindow* _host;

                int _eventID; // Widget Identifier for events
                int _Alignment; // Widget Positioning
                int _initalPos[4]; // Inital distance from window edges
                zCore::zEnumerations::zComponentScale _scale; // Widget Scaling
                zCore::zEventDispatcher& _eventDispatcher;
                
                protected:
                static LRESULT CALLBACK ButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

                public:
                zWin32_zButton(zUI::zWidget::zWindow* window, int eventID, zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, int X, int Y, int Width, int Height, zCore::zEventDispatcher& EvtDispatcher);

                // OVERIDES //
                bool handelEvent(void* eventMsg) override;
                
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

#endif /*_ZWIN32_ZBUTTON_H_*/