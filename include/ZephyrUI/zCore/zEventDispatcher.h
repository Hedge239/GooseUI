#ifndef _ZEVENTDISPATCHER_H_
#define _ZEVENTDISPATCHER_H_

#include "ZephyrUI/zCore/zEvent.h"

#include <unordered_map>
#include <functional>

namespace zUI
{
    namespace zCore
    {
        class zEventDispatcher
        {
            std::unordered_map<int, std::function<void(zEvent)>> EventsObj;

            public:
            void add(const int& eventID, std::function<void(zEvent)> EvtCallback);
            void dispatch(const int& eventID, const zEvent& zEvt);
        };
    }
}

#endif /*_ZEVENTDISPATCHER_H_*/