#include "GooseUI/widgets/window.h"


#ifdef _WIN32

    #ifdef GooseUI_UseWin32
        #include "GooseUI/platform/win32/widgets/win32_window.h"
        #define API goose::platform::gWin32::gWin32_window(title, posistion, width, height);
    #endif

    goose::widget::window* goose::widget::createWindow(std::string title, goose::core::enumerations::windowPos posistion, int width, int height)
    {
        return new API;
    }

#elif defined(__unix__) && !defined(__APPLE__)

    #ifndef GooseUI_UseWayland
    #endif

    #ifndef GooseUI_UseX11
        #include "GooseUI/platform/xorg/widgets/xorg_window.h"
        #define XORG_API goose::platform::gXOrg::gXOrg_window(title, posistion, width, height);
    #endif

    goose::widget::window* goose::widget::createWindow(std::string title, goose::core::enumerations::windowPos posistion, int width, int height)
    {
        /*
        if(std::string(std::getenv("XDG_SESSION_TYPE")) == "x11")
        {
            return new XORG_API; 
        }
        */

        return new XORG_API; // TODO: Replace with wayland
    }

#else

    #error "[GooseUI] -- No OS defined?"

#endif