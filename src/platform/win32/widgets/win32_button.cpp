#include "GooseUI/platform/win32/widgets/win32_button.h"
#include "GooseUI/platform/win32/widgets/win32_window.h"
#include "GooseUI/platform/win32/win32_scaleCalculator.h"

#include "GooseUI/core/eventDispatcher.h"

WNDPROC goose::platform::gWin32::gWin32_button::_OrgProc = nullptr;

namespace goose::platform::gWin32 // INTERNAL
{
    LRESULT CALLBACK gWin32_button::ButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
    {
        gWin32_button* self = reinterpret_cast<gWin32_button*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        switch(uMsg)
        {
            case WM_LBUTTONDOWN:
            {
                if(self)
                {
                    self->onClick();
                }

                break;
            }
            case WM_SIZE:
            {
                RECT adjustedBounds = gWin32::gWin32_scaleCalculator::calculateScaleAndSize(self->_scaleing, self->_alignment, self->_initalPos, hwnd);
                RECT windowBounds; GetClientRect(GetParent(hwnd), &windowBounds);
                
                MoveWindow(hwnd, adjustedBounds.left, adjustedBounds.top, adjustedBounds.right - adjustedBounds.left, adjustedBounds.bottom - adjustedBounds.top, true);
                break;
            }

            break;
        }

        return CallWindowProc(_OrgProc, hwnd, uMsg, wParam, lParam);
    }
}

namespace goose::platform::gWin32 // EXTERNAL
{
    gWin32_button::gWin32_button(widget::window* window, int eventID, goose::core::eventDispatcher& evtDispatcher, goose::core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
    : _evtDispatcher(evtDispatcher), _eventID(eventID), _scaleing(componentScaleing), _alignment(componentAlign)
    {
        _host = dynamic_cast<gWin32_window*>(window);
        _hwnd = CreateWindow(
            "BUTTON",
            "",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            X,
            Y,
            Width,
            Height,
            _host->getHwnd(),
            nullptr,
            nullptr,
            nullptr
        );

        gWin32_button::updateEdgeOffsets();

        SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        _OrgProc = (WNDPROC)SetWindowLongPtr(_hwnd, GWLP_WNDPROC, (LONG_PTR)gWin32_button::ButtonProc);
    }

    // WIDGET SETTINGS
    void gWin32_button::setSize(int Width, int Height) { SetWindowPos(_hwnd, nullptr, 0, 0, Width, Height, SWP_NOZORDER | SWP_NOMOVE); }
    void gWin32_button::setPosistion(int X, int Y) { SetWindowPos(_hwnd, nullptr, X, Y, 0, 0, SWP_NOZORDER | SWP_NOSIZE); }
    void gWin32_button::setLabel(std::string label) { SetWindowTextA(_hwnd, label.c_str()); }
    void gWin32_button::setVisibility(bool isVisible) { if(isVisible) { ShowWindow(_hwnd, SW_SHOW); } else { ShowWindow(_hwnd, SW_HIDE); } }

    // WIDGET MANAGEMENT
    void gWin32_button::updateEdgeOffsets()
    {
        int* t_initalPos;
        t_initalPos = gWin32_scaleCalculator::getDistanceFromWindowEdges(_hwnd);

        _initalPos[0] = t_initalPos[0];
        _initalPos[1] = t_initalPos[1];
        _initalPos[2] = t_initalPos[2];
        _initalPos[3] = t_initalPos[3];
    }

    void gWin32_button::onClick()
    {
        //zCore::zEvent evt{zCore::zEventType::ButtonPress, nullptr};
        core::event::event evt;
        _evtDispatcher.dispatch(_eventID, evt);
    }

    bool gWin32_button::handelEvent(void* evtMsg) {return false;} // Not used for Win32, as we just subclass

    // WIDGET RETURNS
    int gWin32_button::getX() 
    {
        RECT rect;
        GetWindowRect(_hwnd, &rect);

        // Convert to parent client cordinates
        POINT point = { rect.left, rect.top };
        ScreenToClient(_hwnd, &point);

        return point.x;
    }

    int gWin32_button::getY() 
    {
        RECT rect;
        GetWindowRect(_hwnd, &rect);

        // Convert to parent client cordinates
        POINT point = { rect.left, rect.top };
        ScreenToClient(_hwnd, &point);

        return point.y;
    }

    int gWin32_button::getEventID() {return _eventID;}
    
    int gWin32_button::getWidth() { RECT rect; GetWindowRect(_hwnd, &rect); return rect.right - rect.left; }
    int gWin32_button::getHeight() { RECT rect; GetWindowRect(_hwnd, &rect); return rect.bottom - rect.top; }
}