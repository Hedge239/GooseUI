#ifndef _GOOSEUI_BOXBUTTON_H_
#define _GOOSEUI_BOXBUTTON_H_

#include "GooseUI/interfaces/iWindow.h"
#include "GooseUI/interfaces/iWidget.h"
#include "GooseUI/interfaces/iRenderer.h"

#include "GooseUI/core/types.h"
#include "GooseUI/core/eventDispatcher.h"

#include "GooseUI/widgets/base/text.h"

#include "GooseUI/graphics/font/font.h"

#include <string>

namespace goose
{
    namespace widgets
    {
        namespace buttons
        {
            class boxButton : public interface::iWidget
            {
                core::types::color _color;
                core::types::color _labelColor;
                core::event::dispatcher& _evtDispatcher;
                
                int _eventID;
                int _outlineSize;
                
                bool _isPressed;
                
                std::unique_ptr<goose::graphics::font::font> _font = nullptr;
                std::string _label;

                public:
                boxButton(int eventID, goose::core::event::dispatcher& evtDispatcher, core::types::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height);
                ~boxButton() = default;

                void setFont(const std::string& fontFilePath, int size);
                void setLabel(const std::string& text, const core::types::color& color);
                
                void setOutlineSize(int size);
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

            boxButton* createBoxButton(
                int eventID,
                goose::core::event::dispatcher& evtDispatcher, 
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

#endif /*_GOOSEUI_BOXBUTTON_H_*/