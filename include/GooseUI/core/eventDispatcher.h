#ifndef _GOOSEUI_EVENTDISPATCHER_H_
#define _GOOSEUI_EVENTDISPATCHER_H_

#include "GooseUI/core/types.h"

#include <unordered_map>
#include <functional>

namespace goose
{
    namespace core 
    {
        namespace event 
        {
            class dispatcher
            {
                std::unordered_map<int, std::function<void(types::event::eventData)>> EventsObj;

                public:
                void add(const int& eventID, std::function<void(types::event::eventData)> EvtCallback);
                void dispatch(const int& eventID, const types::event::eventData& Evt);
            };
        }
    }
}

#endif /*_GOOSEUI_EVENTDISPATCHER_H_*/