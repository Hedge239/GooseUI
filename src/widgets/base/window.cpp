#include "GooseUI/widgets/base/window.h"

#if defined(_WIN32)

    #include "GooseUI/platform/win32/win32_window.h"
    #define API goose::platform::gWin32::gWin32_window(title, width, height, posistion, graphicsBackend);

    goose::widgets::base::window* goose::widgets::base::createWindow(const std::string& title, int width, int height, goose::core::enumerations::windowPos posistion, goose::core::enumerations::graphicsBackend graphicsBackend)
    {
        return new API;
    }

#elif defined(__unix__) && !defined(__APPLE__)
#else
#endif