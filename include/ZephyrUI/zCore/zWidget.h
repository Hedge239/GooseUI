#ifndef _ZWIDGET_H_
#define _ZWIDGET_H_

#include <ZephyrUI/zCore/zEnumerations.h>

namespace zUI
{
    namespace zWidget
    {
        class zWindow;  // FORWARD DELCERATION
    }

    namespace zCore
    {
        class zEventDispatcher; // FORWARD DELCERATION

        class zWidget
        {
            public:
            virtual ~zWidget() = default;

            // Events
            virtual bool handelEvent(void*) =0; // X11 Only

            virtual void setPos(int X, int Y) = 0;
            virtual void setSize(int Width, int Height) = 0;
            virtual void updateEdgeOffsets() = 0;

            // Returns
            virtual int getEventID() = 0;

            virtual int getX() = 0;
            virtual int getY() = 0;
            virtual int getWidth() = 0;
            virtual int getHeight() = 0;
        };
    }
}

#endif /*_ZWIDGET_H_*/