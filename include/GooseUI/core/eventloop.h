#ifndef _GOOSEUI_EVENTLOOP_H_
#define _GOOSEUI_EVENTLOOP_H_

#include <initializer_list>

namespace goose
{
    namespace interface
    {
        class iWindow; // FORWARD DECLERATION
    }

    namespace core
    {
        class eventloop
        {
            public:
            static void run(std::initializer_list<interface::iWindow*> windows);
        };
    }
}

#endif /*_GOOSEUI_EVENTLOOP_H_*/