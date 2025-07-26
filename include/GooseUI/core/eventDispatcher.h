#ifndef _GOOSEUI_EVENTDISPATCHER_H_
#define _GOOSEUI_EVENTDISPATCHER_H_

#include "GooseUI/core/event.h"

#include <unordered_map>
#include <functional>

namespace goose
{
    namespace core 
    {
        class eventDispatcher
        {
            std::unordered_map<int, std::function<void(event::event)>> EventsObj;

            public:
            void add(const int& eventID, std::function<void(event::event)> EvtCallback);
            void dispatch(const int& eventID, const event::event& Evt);
        };
    }
}

#endif /*_GOOSEUI_EVENTDISPATCHER_H_*/