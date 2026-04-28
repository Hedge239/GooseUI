#include "GooseUI/widgets/window.h"

#if defined(_WIN32)

    #include "GooseUI/platform/win32_window.h"
    #define API GooseUI::platform::win32_window(title, width, height, posistion);

    GooseUI::absractions::iWindow* GooseUI::widgets::createWindow(const std::string& title, int width, int height, GooseUI::screenPosistion posistion)
    {
        return new API;
    }

#elif defined(__unix__) && !defined(__APPLE__)

    #include "GooseUI/platform/x11_window.h"

    GooseUI::absractions::iWindow* GooseUI::widgets::createWindow(const std::string& title, int width, int height, GooseUI::screenPosistion posistion)
    {
        return new GooseUI::platform::x11_window(title, width, height, posistion);
    }
#else
#endif