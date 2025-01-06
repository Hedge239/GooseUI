#ifndef _ZEVENT_H_
#define _ZEVENT_H_

#include <unordered_map>
#include <any>
#include <string>

namespace zUI
{
    namespace zCore
    {
        /*enum class zEventType
        {
            None,
            WindowResize,
            WindowClose,
            ButtonPress,
            ButtonRelease,
            KeyPress,
            KeyRelease,
            MouseMove,
            MouseClick,
            Custom
        };*/

        struct zEvent
        {
            //zEventType EvtType;
            //void* data;
            std::unordered_map<std::string, std::any> data;
        };
    }
}

#endif /*_ZEVENT_H_*/