#include "GooseUI/core/eventloop.h"
#include "GooseUI/core/enumerations.h"
#include "GooseUI/widgets/base/window.h"


#if defined(_WIN32)

    #include <windows.h>

#elif defined(__APPLE__)

    #error Unsuported

#else

    #if GOOSEUI_XORG_SUPPORT
        #include <GooseUI/platform/x11/x11_window.h>
    #endif

    #if GOOSEUI_WAYLAND_SUPPORT
    #endif

#endif


namespace goose::core
{
    void eventloop::run(std::initializer_list<widgets::base::window*> windows)
    {
        int displayService = (*windows.begin())->getDisplayService();
        bool running = false;

        // Begin Loop
        while(true)
        {
            running = false;
            for(widgets::base::window* window : windows)
            {
                if(!window->isRunning()) 
                {
                    window->destroy();
                    continue; 
                }

                running = true;
                window->handelEvents();
            }

            if(!running) { break; }

            #if defined(_WIN32)

            MsgWaitForMultipleObjects(0, nullptr, FALSE, INFINITE, QS_ALLINPUT);
            continue;

            #elif defined(__APPLE__)

            #error TODO
            continue;

            #else

                #if GOOSEUI_XORG_SUPPORT
                if(displayService == core::enumerations::displayService::x11)
                {
                    int lastXfd = 0; 
                    fd_set in_fds;

                    FD_ZERO(&in_fds);
                    for(widgets::base::window* window : windows)
                    {
                        platform::gX11::gX11_window* x11Window = dynamic_cast<platform::gX11::gX11_window*>(window);
                        int xfd = ConnectionNumber(x11Window->getDisplay());
                        FD_SET(xfd, &in_fds); lastXfd = std::max(lastXfd, xfd);
                    }

                    struct timeval timeout { 0, 160000 }; // Temp fix for multi-window, yes I hate it too
                    select(lastXfd + 1, &in_fds, nullptr, nullptr, &timeout);
                    continue;
                }
                #endif

                #if GOOSEUI_WAYLAND_SUPPORT
                if(displayService == core::enumerations::displayService::wayland)
                {

                }
                #endif

            #endif
        }
    }
}