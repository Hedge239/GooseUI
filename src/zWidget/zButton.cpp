#include "ZephyrUI/zWidget/zButton.h"


#ifdef _WIN32

    #ifdef zUseWin32
        #include "ZephyrUI/zPlatform/win32/zWin32_zButton.h"
        #define API zUI::zPlatform::zWin32::zWin32_zButton(window, eventID, zComponentScale, zComponentAlign, X, Y, Width, Height, EvtDispatcher);
    #endif

    zUI::zWidget::zButton* zUI::zWidget::createButton(zWindow* window, int eventID, zUI::zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, int X, int Y, int Width, int Height, zUI::zCore::zEventDispatcher& EvtDispatcher)
    {
        return new API; 
    }

#elif defined(__unix__) && !defined(__APPLE__)

    #ifdef zUseWayland
    #endif

    #ifdef zUseX11
        #include "ZephyrUI/zPlatform/x11/zX11_zButton.h"
        #define x11_API zUI::zPlatform::zX11::zX11_zButton(window, eventID, zComponentScale, zComponentAlign, X, Y, Width, Height, EvtDispatcher);
    #endif

    zUI::zWidget::zButton* zUI::zWidget::createButton(zWindow* window, int eventID, zUI::zCore::zEnumerations::zComponentScale zComponentScale, int zComponentAlign, int X, int Y, int Width, int Height, zUI::zCore::zEventDispatcher& EvtDispatcher)
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