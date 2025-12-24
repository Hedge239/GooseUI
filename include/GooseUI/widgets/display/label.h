#ifndef _GOOSEUI_LABEL_H_
#define _GOOSEUI_LABEL_H_

#include "GooseUI/interfaces/iWindow.h"
#include "GooseUI/interfaces/iWidget.h"
#include "GooseUI/interfaces/iRenderer.h"

#include "GooseUI/core/types.h"

#include "GooseUI/widgets/base/text.h"

#include <string>

namespace goose
{
    namespace widgets
    {
        namespace display
        {
            class label : public interface::iWidget
            {
                core::types::color _color;
                std::unique_ptr<goose::graphics::font::font> _font = nullptr;
                std::string _label;

                public:
                label(core::types::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height);
                ~label() = default;
                
                void setFont(const std::string& fontFilePath, int size);
                void setText(const std::string& label);
                void setColor(const core::types::color& color);
                
                // Overides
                void draw(interface::iRenderer& renderer) override;
                void pollEvent(core::types::event::eventData evtData) override;
                
                void addToWindow(interface::iWindow* window) override;
                void removeFromWindow() override;
                void setParent(iWidget* widget) override;
                void removeParent() override;

                void show() override;
                void hide() override;
                
                void setSize(int width, int height) override;
                void setSizeRestraints(int minWidth, int minHeight, int maxWidth, int maxHeight) override;
                void setPosistion(int X, int Y) override;
            };
            
            label* createLabel(
                core::types::componentScale componentScaleing, 
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