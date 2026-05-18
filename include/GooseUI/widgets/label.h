#ifndef _GOOSEUI_LABEL_H_
#define _GOOSEUI_LABEL_H_

#include "GooseUI/abstractions/iWidget.h"
#include "GooseUI/abstractions/iFont.h"

#include "GooseUI/types.h"

namespace GooseUI
{
    namespace widgets
    {
        class label : public absractions::iWidget
        {
            color _color;
            absractions::iFont* _font;
            std::string _label;

            public:
            label(widgetScaleing widgetScaleing, int widgetAlignment, int x, int y, int width, int height);
            ~label() = default;

            void setFont(const std::string &fontPath, font::fontData fontData);
            void setColor(const color &color);
            void setText(const std::string &text);

            // Overides
            void draw() override;
            void pollEvent(event::data evtData) override;
        };

        label* createLable(
            widgetScaleing widgetScaleing, 
            int widgetAlignment, 
            int x, int y, 
            int width, int height
        );
    }
}

#endif /*_GOOSEUI_LABEL_H_*/