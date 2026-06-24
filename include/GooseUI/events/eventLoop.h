#ifndef _GOOSEUI_EVENTLOOP_H_
#define _GOOSEUI_EVENTLOOP_H_

#include "GooseUI/types.h"

#include <vector>
#include <algorithm>

namespace GooseUI
{
    namespace event
    {
        class loop
        {
            inline static std::vector<absractions::iWindow*> _windows;
            
            public:
            static void add(absractions::iWindow* window);
            static void remove(absractions::iWindow* window);

            static void run();
        };
    }
}

#endif /*_GOOSEUI_EVENTLOOP_H_*/