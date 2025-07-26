#ifndef _GOOSEUI_EVENT_H_
#define _GOOSEUI_EVENT_H_

#include <unordered_map>
#include <any>
#include <string>

namespace goose 
{
    namespace core 
    {
        namespace event 
        {
            /*enum class zEventType
            {
                None,
                WindowResize,
                WindowClose,
                uttonPress,
                ButtonRelease,
                KeyPress,
                KeyRelease,
                MouseMove,
                MouseClick,
                Custom
            };*/

            struct event
            {
                //zEventType EvtType;
                //void* data;
                std::unordered_map<std::string, std::any> data;
            };
        }
    }
}

#endif /*_GOOSEUI_EVENT_H_*/