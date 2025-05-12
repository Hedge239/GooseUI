#include "ZephyrUI/zWidget/zWindow.h"


#ifdef _WIN32

    #ifdef zUseWin32
        #include "ZephyrUI/zPlatform/win32/zWin32_zWindow.h"
        #define API zUI::zPlatform::zWin32::zWin32_zWindow(title, windowPos, width, height);
    #endif

    zUI::zWidget::zWindow* zUI::zWidget::createWindow(std::string title, zUI::zCore::zEnumerations::zWindowPos windowPos, int width, int height)
    {
        return new API; 
    }

#elif defined(__unix__) && !defined(__APPLE__)

    // TODO
    // Just storeing this here | std::string(std::getenv("XDG_SESSION_TYPE")) == "x11"
    #ifdef zUseWayland
    #endif

    #ifdef zUseX11
        #include "ZephyrUI/zPlatform/x11/zX11_zWindow.h"
        #define x11_API zUI::zPlatform::zX11::zX11_zWindow(title, windowPos, width, height);
    #endif

    zUI::zWidget::zWindow* zUI::zWidget::createWindow(std::string title, zUI::zCore::zEnumerations::zWindowPos windowPos, int width, int height)
    {
        /*
        if(std::string(std::getenv("XDG_SESSION_TYPE")) == "x11")
        {
            return new x11_API; 
        }
        */

        return new x11_API; // temp
    }

#else

    #error "ZephyrUI: No Defined Display Service

#endif