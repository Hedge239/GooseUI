#include "ZephyrUI/zPlatform/win32api/win32api.h"
#include "ZephyrUI/zPlatform/win32api/win32api_zButton.h"
#include "ZephyrUI/zPlatform/win32api/win32api_zWindow.h"

#include "ZephyrUI/zCore/zEventDispatcher.h"

using namespace zUI;
using namespace zPlatform;
using namespace Win32API;

WNDPROC Win32API_Button::_OrgProc = nullptr;

Win32API_Button::Win32API_Button(zUI::zWidget::zWindow* window, int eventID, zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, int X, int Y, int Width, int Height, zCore::zEventDispatcher& EvtDispatcher)
    :  _eventDispatcher(EvtDispatcher), _eventID(eventID), _scale(zComponentScale), _Alignment(zComponentAlign)
    {
        _host = dynamic_cast<Win32API_Window*>(window);
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

    Win32API_Button::updateEdgeOffsets();
    
    // I tried using the new method of subclassing, but I got so mad at the documentation this is where I ended at
    SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    _OrgProc = (WNDPROC)SetWindowLongPtr(_hwnd, GWLP_WNDPROC, (LONG_PTR)Win32API_Button::ButtonProc);
}

// Window Settings
void Win32API_Button::updateEdgeOffsets()
{
    int* t_initalPos;
    t_initalPos = WidgetAPI::getDistanceFromWindowEdges(_hwnd);

    _initalPos[0] = t_initalPos[0];
    _initalPos[1] = t_initalPos[1];
    _initalPos[2] = t_initalPos[2];
    _initalPos[3] = t_initalPos[3];
}

void Win32API_Button::setPos(int X, int Y) {}
void Win32API_Button::setSize(int Width, int Height) {}
void Win32API_Button::setLabel(std::string text) {SetWindowTextA(_hwnd, text.c_str());}

// Returns
int Win32API_Button::getEventID() {return 0;}
int Win32API_Button::getX() {return 0;}
int Win32API_Button::getY() {return 0;}
int Win32API_Button::getWidth() {return 0;}
int Win32API_Button::getHeight() {return 0;}

// Widget Management
void Win32API_Button::onClick()
{
    //zCore::zEvent evt{zCore::zEventType::ButtonPress, nullptr};
    zCore::zEvent evt;
    _eventDispatcher.dispatch(_eventID, evt);
}

LRESULT CALLBACK Win32API_Button::ButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    Win32API_Button* button = reinterpret_cast<Win32API_Button*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    
    switch (uMsg)
    {
        case WM_LBUTTONDOWN:
        {
            if(button)
            {
                button->onClick(); 
            }
            
            break;
        }
        case WM_SIZE:
        {
            RECT adjustedBounds = WidgetAPI::calculateScaleAndSize(button->_scale, button->_Alignment, button->_initalPos, hwnd);
            RECT windowBounds; GetClientRect(GetParent(hwnd), &windowBounds);
            
            MoveWindow(hwnd, adjustedBounds.left, adjustedBounds.top, adjustedBounds.right - adjustedBounds.left, adjustedBounds.bottom - adjustedBounds.top, true);
            break;
        }

        break;
    }

    return CallWindowProc(_OrgProc, hwnd, uMsg, wParam, lParam);
}