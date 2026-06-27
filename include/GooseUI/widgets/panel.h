#ifndef _GOOSEUI_PANEL_H_
#define _GOOSEUI_PANEL_H_

#include "GooseUI/abstractions/iWidget.h"

#include "GooseUI/types.h"

namespace GooseUI
{
    namespace widgets
    {
        class panel : public absractions::iWidget
        {
            color _color;
            color _outlineColor;

            int _outlineSize;

            public:
            panel(widgetScaleing widgetScaleing, int widgetAlignment, int x, int y, int width, int height);
            ~panel() = default;

            void setColor(const color& color);
            void setOutlineColor(const color& color);
            void setOutlineSize(int size);

            // Overides
            void draw() override;
            void pollEvent(event::data evtData) override;
        };

        panel* createPanel(
            widgetScaleing widgetScaleing, 
            int widgetAlignment, 
            int x, int y, 
            int width, int height
        );
    }
}

#endif /*_GOOSEUI_PANEL_H_*/