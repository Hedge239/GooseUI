#ifndef _GOOSEUI_PANEL_H_
#define _GOOSEUI_PANEL_H_

#include "GooseUI/core/templates/widgetBase.h"
#include "GooseUI/core/templates/renderBase.h"

#include "GooseUI/core/enumerations.h"
#include "GooseUI/core/event.h"

#include "GooseUI/widgets/base/window.h"
#include "GooseUI/graphics/layoutCalculator.h"

#include <vector>

namespace goose
{
    namespace widgets
    {
        namespace display
        {
            class panel : public core::templates::widget::base
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
                
                std::vector<core::templates::widget::base*> _widgets;
                
                public:
                panel(widgets::base::window* window, core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height);
                ~panel();
                
                void addChild(core::templates::widget::base* widget);
                void removeChild(core::templates::widget::base* widget);
                
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
            
            panel* createPanel(
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

#endif /*_GOOSEUI_PANEL_H_*/