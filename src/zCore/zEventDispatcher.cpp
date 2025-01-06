#include "ZephyrUI/zCore/zEventDispatcher.h"

using namespace zUI;
using namespace zCore;


void zEventDispatcher::dispatch(const int& eventID, const zEvent& zEvt)
{
    if(zEventDispatcher::EventsObj.count(eventID))
    {
        zEventDispatcher::EventsObj[eventID](zEvt);
    }
}

void zEventDispatcher::add(const int& eventID, std::function<void(zEvent)> EvtCallback) {zEventDispatcher::EventsObj[eventID] = EvtCallback;}