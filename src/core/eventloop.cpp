#include "GooseUI/core/eventloop.h"
#include "GooseUI/widgets/base/window.h"

#include <vector>

#if defined(_WIN32)
    #include <windows.h>
#else
    // TODO: Linux & MacOS
#endif

namespace goose::core
{
    void eventloop::run(std::initializer_list<widgets::base::window*> windows)
    {
        // I solely did this just so the user did not have to init vector first
        //std::vector<widgets::base::window*> window_vec(windows);

        while(true)
        {
            bool running = false;

            for(widgets::base::window* window : windows)
            {
                // TODO FIX: When window is not running, remove from vector then destroy then continue. This will only run once per destroyed window
                if(!window->isRunning()) 
                {
                    window->destroy();
                    continue; 
                }

                running = true;

                window->handelEvents();
            }

            if(!running) { break; }

            // Platform specific code for performance
            #if defined(_WIN32)
            MsgWaitForMultipleObjects(0, nullptr, FALSE, INFINITE, QS_ALLINPUT);
            #else
            // TODO: Linux & MacOS
            #endif
        }
    }
}