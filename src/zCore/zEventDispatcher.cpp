#include "ZephyrUI/zCore/zEventDispatcher.h"

using namespace zUI;
using namespace zCore;


void zEventDispatcher::dispatch(const zEvent& zEvt)
{
    if(zEventDispatcher::EventsObj.count(zEvt.EvtType))
    {
        for(const auto& callback : zEventDispatcher::EventsObj[zEvt.EvtType])
        {
            callback(zEvt);
        }
    }
}

void zEventDispatcher::add(zEventType EvtType, std::function<void(zEvent)> EvtCallback) {zEventDispatcher::EventsObj[EvtType].push_back(EvtCallback);}