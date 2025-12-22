#include "GooseUI/widgets/base/window.h"

#if defined(_WIN32)

    #include "GooseUI/platform/win32/win32_window.h"
    #define API goose::platform::gWin32::gWin32_window(title, width, height, posistion, graphicsBackend);

    goose::interface::iWindow* goose::widgets::base::createWindow(const std::string& title, int width, int height, core::types::windowPosistion posistion, core::types::graphicsBackend graphicsBackend)
    {
        return new API;
    }

#elif defined(__unix__) && !defined(__APPLE__)

    #include "GooseUI/platform/x11/x11_window.h"

    goose::interface::iWindow* goose::widgets::base::createWindow(const std::string& title, int width, int height, core::types::windowPosistion posistion, core::types::graphicsBackend graphicsBackend)
    {
        return new goose::platform::gX11::gX11_window(title, width, height, posistion, graphicsBackend);
    }
#else
#endif