#include "ZephyrUI/zWidget/zWindow.h"

#ifdef _WIN32

    #ifdef zUseWin32API
        #include "ZephyrUI/zPlatform/win32api/win32api_zWindow.h"
        #define API zUI::zPlatform::Win32API::Win32API_Window(title, windowPos, width, height);
    #endif

    zUI::zWidget::zWindow* zUI::zWidget::createWindow(std::string title, zUI::zCore::zEnumerations::zWindowPos windowPos, int width, int height)
    {
        return new API; 
    }

#elif defined(__unix__) && !defined(__APPLE__)

    // TODO
    // Just storeing this here | std::string(std::getenv("XDG_SESSION_TYPE")) == "x11"

#else

    #error "ZephyrUI: No Defined Display Service

#endif