#include "GooseUI/core/eventDispatcher.h"

namespace goose::core::event
{
    void dispatcher::dispatch(const int& eventID, const event& Evt)
    {
        if(dispatcher::EventsObj.count(eventID))
        {
            dispatcher::EventsObj[eventID](Evt);
        }
    }

    void dispatcher::add(const int& eventID, std::function<void(event)> EvtCallback) { dispatcher::EventsObj[eventID] = EvtCallback; }
}