#ifndef _GOOSEUI_WIDGET_BASE_H_
#define _GOOSEUI_WIDGET_BASE_H_

namespace goose 
{
    namespace core 
    {
        class eventDispatcher; // FORWARD DELCERATION
    }

    namespace widget
    {
        class window; // FORWARD DELCERATION

        class widget_base
        {
            public:
            virtual ~widget_base() = default;

            // Events
            virtual bool handelEvent(void* evtMsg) = 0;

            virtual void updateEdgeOffsets() = 0;
            virtual void setSize(int Width, int Height) = 0;
            virtual void setPosistion(int X, int Y) = 0;

            // Returns
            virtual int getEventID() = 0;

            virtual int getX() = 0;
            virtual int getY() = 0;
            virtual int getWidth() = 0;
            virtual int getHeight() = 0;
        };
    }
}

#endif /*_GOOSEUI_WIDGET_BASE_H_*/