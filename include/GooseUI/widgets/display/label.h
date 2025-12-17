#ifndef _GOOSEUI_LABEL_H_
#define _GOOSEUI_LABEL_H_

#include "GooseUI/core/templates/widgetBase.h"
#include "GooseUI/core/templates/renderBase.h"

#include "GooseUI/core/enumerations.h"
#include "GooseUI/core/event.h"

#include "GooseUI/widgets/base/text.h"
#include "GooseUI/graphics/layoutCalculator.h"

#include "GooseUI/widgets/base/window.h"

#include <string>

namespace goose
{
    namespace widgets
    {
        namespace display
        {
            class label : public core::templates::widget::base
            {
                widgets::base::window* _host;

                graphics::layout::sizeRestraints _sizeRestraints;
                core::templates::renderBase::color _color;
                core::enumerations::componentScale _scaleMethod;
                
                bool _isVisible;
                
                int _initalBounds[4];
                int _alignment;
                int _width, _height;
                int _minWidth, _minHeight;
                int _posX, _posY;
                
                std::unique_ptr<goose::graphics::font::font> _font = nullptr;
                std::string _label;

                public:
                label(widgets::base::window* window, core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height);
                ~label() = default;
                
                void setFont(const std::string& fontFilePath, int size);
                void setText(const std::string& label);
                void setColor(core::templates::renderBase::color color);
                
                // Overides
                // Core Functions
                void draw(core::templates::renderBase::renderer& renderer) override;
                void handelEvent(core::event::event evtData) override;

                // Visibility
                void show() override;
                void hide() override;

                // Posistioning
                void setSize(int width, int height) override;
                void setSizeRestraints(int minWidth, int minHeight, int maxWidth, int maxHeight) override;
                void setPosistion(int X, int Y) override;

                // Return
                int getEventID() override;

                int getX() override;
                int getY() override;
                int getWidth() override;
                int getHeight() override;
            };
            
            label* createLabel(
                widgets::base::window* window,
                core::enumerations::componentScale componentScaleing, 
                int componentAlign, 
                int X, 
                int Y, 
                int Width, 
                int Height
            );
        }
    }
}

#endif /*_GOOSEUI_LABEL_H_*/