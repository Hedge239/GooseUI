#ifndef _GOOSEUI_EVENTLOOP_H_
#define _GOOSEUI_EVENTLOOP_H_

#include "GooseUI/types.h"

#include <initializer_list>

namespace GooseUI
{
    namespace event
    {
        class loop
        {
            public:
            static void run(std::initializer_list<absractions::iWindow*> windows);
        };
    }
}

#endif /*_GOOSEUI_EVENTLOOP_H_*/