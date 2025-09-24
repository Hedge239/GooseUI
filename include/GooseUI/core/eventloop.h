#ifndef _GOOSEUI_EVENTLOOP_H_
#define _GOOSEUI_EVENTLOOP_H_

#include <vector>

namespace goose
{
    namespace widgets
    {
        namespace base
        {
            class window; // FORWARD DELCERATION
        }
    }

    namespace core
    {
        class eventloop
        {
            public:
            static void run(std::initializer_list<widgets::base::window*> windows);
        };
    }
}

#endif /*_GOOSEUI_EVENTLOOP_H_*/