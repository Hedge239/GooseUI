#include "ZephyrUI/zWidget/zButton.h"

#ifdef _WIN32

    #ifdef zUseWin32API
        #include "ZephyrUI/zPlatform/win32api/win32api_zButton.h"
        #define API zUI::zPlatform::Win32API::Win32API_Button(window, eventID, X, Y, Width, Height, EvtDispatcher);
    #endif

    zUI::zWidget::zButton* zUI::zWidget::createButton(zWindow* window, int eventID, int X, int Y, int Width, int Height, zUI::zCore::zEventDispatcher& EvtDispatcher)
    {
        return new API; 
    }

#elif defined(__unix__) && !defined(__APPLE__)

    // TODO
    // Just storeing this here | std::string(std::getenv("XDG_SESSION_TYPE")) == "x11"

#else

    #error "ZephyrUI: No Defined Display Service

#endif