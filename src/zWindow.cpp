#include "ZephyrUI/zWindow.h"
#include "ZephyrUI/ZephyrUI.h"

#include <unordered_map>
#include <iostream>

#ifdef _WIN32
    #include "ZephyrUI/lib/Win32/w32_window.h"
#elif defined(__unix__)
    #ifdef X11_SUPPORT
        #include "ZephyrUI/lib/XOrg/x11_window.h"
    #endif
        #include "ZephyrUI/lib/Wayland/wl_window.h"
#else
    #error "Not Supported Operating System"
#endif


namespace zephyr
{
    // Still no clue on what this does, all I know is it instance the window
    zWindow::zWindow() {}

    zWindow::zWindow(zWindowConfig windowCfg)
    {
        _WindowConfig = windowCfg;
    }
    
    // Window Creation System
    void zWindow::create()
    {
        std::cout << "[ZephyrUI] zWindow.cpp -> CreateWindow: Creating Window -> " << _WindowConfig.className << std::endl;

        #ifdef _WIN32
            lib::w32_CreateWindow(_WindowConfig);
        #elif
        #else
            #error "Not Supported Operating System"
        #endif
    }

    void zWindow::close()
    {
        std::cout << "[ZephyrUI] zWindow.cpp -> CreateWindow: Closeing Window -> " << _WindowConfig.className << std::endl;

        #ifdef _WIN32
            lib::w32_CloseWindow();
        #elif
        #else
            #error "Not Supported Operating System"
        #endif
    }

    // Window Sorting System
    std::unordered_map<std::string, zWindow> ExsistingWindows;

    void CreateWindow(zWindowConfig zWindowConfig)
    {
        if(zWindowConfig.className.empty())
        {
            std::cout <<  "[ZephyrUI] zWindow.cpp -> CreateWindow: Can not create window with empty class name!" << std::endl;
        }else
        {
            zWindow window(zWindowConfig);
            ExsistingWindows[zWindowConfig.className] = window;
            window.create();
        }
    }

    void CloseWindow(std::string className)
    {
        auto target = ExsistingWindows.find(className);
        if(target != ExsistingWindows.end())
        {
            ExsistingWindows.erase(target);
            target->second.close();
        }else
        {
            std::cout <<  "[ZephyrUI] zWindow.cpp -> CloseWindow: Faild to find class -> " << className << std::endl;
        }
    }

    namespace WindowManager
    {
        void RemoveWindowFromMap(std::string className)
        {
            auto target = ExsistingWindows.find(className);
            if(target != ExsistingWindows.end())
            {
                ExsistingWindows.erase(target);
            }else
            {
                std::cout <<  "[ZephyrUI] zWindow.cpp -> RemoveWindowFromMap: Faild to find class -> " << className << std::endl;
            }
        }
    }
}