#ifndef _ZEVENTDISPATCHER_H_
#define _ZEVENTDISPATCHER_H_

#include "ZephyrUI/zCore/zEvent.h"

#include <map>
#include <functional>

namespace zUI
{
    namespace zCore
    {
        class zEventDispatcher
        {
            std::map<zEventType, std::vector<std::function<void(zEvent)>>> EventsObj;

            public:
            void add(zEventType EvtType, std::function<void(zEvent)> EvtCallback);
            void dispatch(const zEvent& zEvt);
        };
    }
}

#endif /*_ZEVENTDISPATCHER_H_*/