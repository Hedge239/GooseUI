#ifndef _GOOSEUI_PANEL_H_
#define _GOOSEUI_PANEL_H_

#include "GooseUI/interfaces/iWindow.h"
#include "GooseUI/interfaces/iWidget.h"
#include "GooseUI/interfaces/iRenderer.h"

#include "GooseUI/core/types.h"

// Oops did most of the rewright :3
// TODO: Add a proigateing system for window-AddWidget(), so you only have to add the inital parent and then all children will be added
// Low priority tho unlike the rewright, since this actaully work correctly (for pos and scale management)
// Update: Higher Priority now, relized that if I dont you will have widgets under other widgets and visibility would be a mess

namespace goose
{
    namespace widgets
    {
        namespace containers
        {
            class panel : public interface::iWidget
            {
                core::types::color _color;
                
                public:
                panel(core::types::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height);
                ~panel() = default;
                
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
            
            panel* createPanel(
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

#endif /*_GOOSEUI_PANEL_H_*/