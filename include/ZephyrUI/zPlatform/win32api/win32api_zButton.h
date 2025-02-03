#ifndef _WIN32API_ZBUTTON_H_
#define _WIN32API_ZBUTTON_H_

#include <windows.h>
#include "ZephyrUI/zWidget/zButton.h"

namespace zUI
{
    namespace zPlatform
    {
        namespace Win32API
        {
            class Win32API_Window;

            class Win32API_Button : public zWidget::zButton
            {
                HWND _hwnd;
                static WNDPROC _OrgProc; 
                Win32API_Window* _host;

                int _eventID; // Widget Identifier for events
                int _Alignment; // Widget Positioning
                int _initalPos[4]; // Inital distance from window edges
                zCore::zEnumerations::zComponentScale _scale; // Widget Scaling
                zCore::zEventDispatcher& _eventDispatcher;
                
                protected:
                static LRESULT CALLBACK ButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

                public:
                Win32API_Button(zUI::zWidget::zWindow* window, int eventID, zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, int X, int Y, int Width, int Height, zCore::zEventDispatcher& EvtDispatcher);

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

#endif /*_WIN32API_ZBUTTON_H_*/