#include "GooseUI/core/eventDispatcher.h"


void goose::core::eventDispatcher::dispatch(const int& eventID, const event::event& Evt)
{
    if(goose::core::eventDispatcher::EventsObj.count(eventID))
    {
        goose::core::eventDispatcher::EventsObj[eventID](Evt);
    }
}

void goose::core::eventDispatcher::add(const int& eventID, std::function<void(event::event)> EvtCallback) {goose::core::eventDispatcher::EventsObj[eventID] = EvtCallback;}