#ifndef _GOOSEUI_BOXBUTTON_H_
#define _GOOSEUI_BOXBUTTON_H_

#include "GooseUI/core/templates/widgetBase.h"
#include "GooseUI/core/templates/renderBase.h"

#include "GooseUI/widgets/base/window.h"

#include "GooseUI/core/enumerations.h"
#include "GooseUI/core/eventDispatcher.h"
#include "GooseUI/core/event.h"

#include <string>

namespace goose
{
    namespace widgets
    {
        namespace buttons
        {
            class boxButton : public core::templates::widget::base
            {
                widgets::base::window* _host;

                core::templates::renderBase::color _color;
                core::enumerations::componentScale _scaleMethod;
                core::event::dispatcher& _evtDispatcher;

                int _initalBounds[4];

                bool _isPressed;
                bool _isVisible;

                int _outlineSize;
                int _eventID;
                int _alignment;
                int _width, _height;
                int _posX, _posY;

                std::string _label;

                public:
                boxButton(widgets::base::window* window, int eventID, goose::core::event::dispatcher& evtDispatcher, goose::core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height);
                ~boxButton() = default;

                void setLabel(std::string label);
                void setOutlineSize(int size);

                // Overides
                // Core Functions
                void draw(core::templates::renderBase::renderer& renderer) override;
                void handelEvent(core::event::event evtData) override;

                // Visibility
                void show() override;
                void hide() override;

                // Posistioning
                void setSize(int width, int height) override;
                void setPosistion(int X, int Y) override;

                // Return
                int getEventID() override;

                int getX() override;
                int getY() override;
                int getWidth() override;
                int getHeight() override;
            };

            boxButton* createBoxButton(
                widgets::base::window* window,
                int eventID,
                goose::core::event::dispatcher& evtDispatcher, 
                goose::core::enumerations::componentScale componentScaleing, 
                int componentAlign, 
                int X, 
                int Y, 
                int Width, 
                int Height
            );
        }
    }
}

#endif /*_GOOSEUI_BOXBUTTON_H_*/