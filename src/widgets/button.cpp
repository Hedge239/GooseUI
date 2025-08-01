#include "GooseUI/widgets/button.h"


#ifdef _WIN32

    #ifdef GooseUI_UseWin32
        #include "GooseUI/platform/win32/widgets/win32_button.h"
        #define API goose::platform::gWin32::gWin32_button(window, eventID, evtDispatcher, componentScaleing, componentAlign, X, Y, Width, Height);
    #endif

    goose::widget::button* goose::widget::createButton(window *window, int eventID, goose::core::eventDispatcher &evtDispatcher, goose::core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
    {
        return new API;
    }

#elif defined(__unix__) && !defined(__APPLE__)

    #ifndef GooseUI_UseWayland
    #endif

    #ifndef GooseUI_UseX11
        #include "GooseUI/platform/xorg/widgets/xorg_button.h"
        #define XORG_API goose::platform::gXOrg::gXOrg_button(window, eventID, evtDispatcher, componentScaleing, componentAlign, X, Y, Width, Height);
    #endif
    
    goose::widget::button* goose::widget::createButton(window *window, int eventID, goose::core::eventDispatcher &evtDispatcher, goose::core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
    {
        /*
        if(std::string(std::getenv("XDG_SESSION_TYPE")) == "x11")
        {
            return new XORG_API; 
        }*/
        
        return new XORG_API; // TODO: Replace with wayland
    }
    

#else

    #error "[GooseUI] -- No OS defined?!?"

#endif