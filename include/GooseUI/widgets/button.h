#ifndef _GOOSEUI_BUTTON_H_
#define _GOOSEUI_BUTTON_H_

#include "GooseUI/core/enumerations.h"
#include "GooseUI/widgets/widget_base.h"

#include <string>

namespace goose 
{
    namespace widget 
    {
        class button : public widget_base
        {
            public:
            virtual ~button() = default;

            virtual void onClick() = 0;

            virtual void setVisibility(bool isVisible) = 0;
            virtual void setLabel(std::string label) = 0;
        };

        button* createButton(
            window* window, 
            int eventID, 
            goose::core::eventDispatcher& evtDispatcher, 
            goose::core::enumerations::componentScale componentScaleing, 
            int componentAlign, 
            int X, int Y, int Width, int Height
        );
    }
}

#endif /*_GOOSEUI_BUTTON_H_*/