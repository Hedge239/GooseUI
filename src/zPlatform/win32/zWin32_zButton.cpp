#include "ZephyrUI/zPlatform/win32/zWin32.h"
#include "ZephyrUI/zPlatform/win32/zWin32_zButton.h"
#include "ZephyrUI/zPlatform/win32/zWin32_zWindow.h"

#include "ZephyrUI/zCore/zEventDispatcher.h"

using namespace zUI;
using namespace zPlatform;
using namespace zWin32;

WNDPROC zWin32_zButton::_OrgProc = nullptr;


zWin32_zButton::zWin32_zButton(zUI::zWidget::zWindow* window, int eventID, zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, int X, int Y, int Width, int Height, zCore::zEventDispatcher& EvtDispatcher)
    :  _eventDispatcher(EvtDispatcher), _eventID(eventID), _scale(zComponentScale), _Alignment(zComponentAlign)
    {
        _host = dynamic_cast<zWin32_zWindow*>(window);
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

    zWin32_zButton::updateEdgeOffsets();
    
    // I tried using the new method of subclassing, but I got so mad at the documentation this is where I ended at
    SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    _OrgProc = (WNDPROC)SetWindowLongPtr(_hwnd, GWLP_WNDPROC, (LONG_PTR)zWin32_zButton::ButtonProc);
}

// Window Settings
void zWin32_zButton::updateEdgeOffsets()
{
    int* t_initalPos;
    t_initalPos = zWin32_WidgetAPI::getDistanceFromWindowEdges(_hwnd);

    _initalPos[0] = t_initalPos[0];
    _initalPos[1] = t_initalPos[1];
    _initalPos[2] = t_initalPos[2];
    _initalPos[3] = t_initalPos[3];
}

void zWin32_zButton::setPos(int X, int Y) {}
void zWin32_zButton::setSize(int Width, int Height) {}
void zWin32_zButton::setLabel(std::string text) {SetWindowTextA(_hwnd, text.c_str());}

// Returns
int zWin32_zButton::getEventID() {return 0;}
int zWin32_zButton::getX() {return 0;}
int zWin32_zButton::getY() {return 0;}
int zWin32_zButton::getWidth() {return 0;}
int zWin32_zButton::getHeight() {return 0;}

// Widget Management
bool zWin32_zButton::handelEvent(void* eventMsg) {return false;}; // Not used for windows, we just subclass the proc

void zWin32_zButton::onClick()
{
    //zCore::zEvent evt{zCore::zEventType::ButtonPress, nullptr};
    zCore::zEvent evt;
    _eventDispatcher.dispatch(_eventID, evt);
}

LRESULT CALLBACK zWin32_zButton::ButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    zWin32_zButton* button = reinterpret_cast<zWin32_zButton*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    
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
            RECT adjustedBounds = zWin32_WidgetAPI::calculateScaleAndSize(button->_scale, button->_Alignment, button->_initalPos, hwnd);
            RECT windowBounds; GetClientRect(GetParent(hwnd), &windowBounds);
            
            MoveWindow(hwnd, adjustedBounds.left, adjustedBounds.top, adjustedBounds.right - adjustedBounds.left, adjustedBounds.bottom - adjustedBounds.top, true);
            break;
        }

        break;
    }

    return CallWindowProc(_OrgProc, hwnd, uMsg, wParam, lParam);
}
