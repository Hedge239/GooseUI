#ifndef _ZEVENT_H_
#define _ZEVENT_H_

namespace zUI
{
    namespace zCore
    {
        enum class zEventType
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
        };

        struct zEvent
        {
            zEventType EvtType;
            void* data;
        };
    }
}

#endif /*_ZEVENT_H_*/