#ifndef _GOOSEUI_WIDGET_BASE_H_
#define _GOOSEUI_WIDGET_BASE_H_

namespace goose
{
    namespace core
    {
        namespace event
        {
            struct event; // FORWARD DELCERATION
        }

        namespace templates
        {
            namespace renderBase
            {
                class renderer; // FORWARD DELCERATION
                struct color; // FORWARD DELCERATION
            }

            namespace widget
            {
                class base
                {
                    public:
                    virtual ~base() = default;

                    // Core Functions
                    virtual void draw(renderBase::renderer& renderer) = 0;
                    virtual void handelEvent(event::event evtData) = 0;

                    // Visibility
                    virtual void show() = 0;
                    virtual void hide() = 0;

                    // Posistioning
                    virtual void setSize(int width, int height) = 0;
                    virtual void setSizeRestraints(int minWidth, int minHeight, int maxWidth, int maxHeight) = 0;
                    virtual void setPosistion(int X, int Y) = 0;

                    // Return
                    virtual int getEventID() = 0;

                    virtual int getX() = 0;
                    virtual int getY() = 0;
                    virtual int getWidth() = 0;
                    virtual int getHeight() = 0;
                };
            }
        }
    }
}

#endif /*_GOOSEUI_WIDGET_BASE_H_*/