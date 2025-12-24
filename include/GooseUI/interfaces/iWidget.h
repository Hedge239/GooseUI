#ifndef _GOOSEUI_IWIDGET_H_
#define _GOOSEUI_IWIDGET_H_

#include "GooseUI/core/types.h"

namespace goose
{
    namespace interface
    {
        class iWindow;      // FORWARD DECLERATION
        class iRenderer;    // FORWARD DECLERATION
        
        class iWidget
        {
            protected:
            iWindow* _hostWindow = nullptr;
            iWidget* _hostParent = nullptr;
            
            bool _isVisible = false;
            
            core::types::sizeRestraints _sizeRestraints;
            core::types::componentScale _scaleing;
            
            int _initalBounds[4];
            int _alignment;
            
            int _posX, _posY;
            int _width, _height;
            
            public:
            virtual ~iWidget() = default;
            
            // Core
            virtual void draw(iRenderer& renderer) = 0;
            virtual void pollEvent(core::types::event::eventData evtData) = 0;
            
            virtual void addToWindow(iWindow* window) = 0;
            virtual void removeFromWindow() = 0;
            virtual void setParent(iWidget* widget) = 0;
            virtual void removeParent() = 0;
            
            // Visiblity
            virtual void show() = 0;
            virtual void hide() = 0;
            
            // Posistioning
            virtual void setSize(int width, int height) = 0;
            virtual void setSizeRestraints(int minWidth, int minHeight, int maxWidth, int maxHeight) = 0;
            virtual void setPosistion(int X, int Y) = 0;
            
            // Returmns
            iWindow* getWindow() const { return _hostWindow; }
            
            bool isVisible() const { return _isVisible; }
            
            int getPosX() const { return _posX; };
            int getPosY() const { return _posY; }
            int getWidth() const { return _width; }
            int getHeight() const { return _height; }
        };
    }
}

#endif /*_GOOSEUI_IWIDGET_H_*/