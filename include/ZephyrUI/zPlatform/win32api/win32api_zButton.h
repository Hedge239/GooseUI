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
                zCore::zEventDispatcher& _eventDispatcher;
                Win32API_Window* _host;

                int posX, posY, width, height, uniqueID;
                
                protected:
                static LRESULT CALLBACK ButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

                public:
                Win32API_Button(zUI::zWidget::zWindow* window, int X, int Y, int Width, int Height, zCore::zEventDispatcher& EvtDispatcher);

                // OVERIDES //
                void setPos(int X, int Y) override;
                void setSize(int Width, int Height) override;

                int getX() override;
                int getY() override;
                int getWidth() override;
                int getHeight() override;
                
                void onClick() override;
            };
        }
    }
}

#endif /*_WIN32API_ZBUTTON_H_*/