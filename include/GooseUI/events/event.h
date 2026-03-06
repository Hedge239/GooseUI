#ifndef _GOOSEUI_EVENT_H_
#define _GOOSEUI_EVENT_H_

namespace GooseUI
{
    namespace event
    {
        enum class type
        {
            none,
            leftMouseDown,
            leftMouseUp,
            rightMouseDown
        };
        
        struct data
        {
            type type = type::none;

            float mouseX = 0;
            float mouseY = 0;
        };
    }
}

#endif /*_GOOSEUI_EVENT_H_*/