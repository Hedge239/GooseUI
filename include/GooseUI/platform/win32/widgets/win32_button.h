#ifndef _GOOSEUI_WIN32_BUTTON_H_
#define _GOOSEUI_WIN32_BUTTON_H_

#include "GooseUI/widgets/button.h"

#include <windows.h>

namespace goose
{
    namespace platform
    {
        namespace gWin32    // We will put "g" infront to prevent conflicts
        {
            class gWin32_window;    // FORWARD DECLERATION

            class gWin32_button : public widget::button
            {
                HWND _hwnd;
                gWin32_window* _host;

                static WNDPROC _OrgProc;

                int _eventID;
                int _alignment;
                int _initalPos[4];

                core::enumerations::componentScale _scaleing;
                core::eventDispatcher& _evtDispatcher;

                protected:
                static LRESULT CALLBACK ButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

                public:
                gWin32_button(widget::window* window, int eventID, goose::core::eventDispatcher& evtDispatcher, goose::core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height);
                
                // OVERIDES //
                bool handelEvent(void*) override;

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

#endif /*_GOOSEUI_WIN32_BUTTON_H_*/