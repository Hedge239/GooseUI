#ifndef _GOOSEUI_EVENT_H_
#define _GOOSEUI_EVENT_H_

namespace goose 
{
    namespace core 
    {
        namespace event 
        {
            // Changed how this works, now it used to pass data from the window to the widget (Ie mouse posistion) instead of data from widget to user
            // I will just add more functions like getText() or whatnot
            enum class eventType
            {
                none,
                leftMouseDown,
                leftMouseUp,
                rightMouseDown,
            };

            struct event
            {
                eventType type = eventType::none;

                float mouseX = 0;
                float mouseY = 0;
            };
        }
    }
}

#endif /*_GOOSEUI_EVENT_H_*/