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
            
            core::types::layoutRestraints _sizeRestraints;
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
            
            // Pre-Defiend Fixed Functions - All widgets need these and my hand hurts :<
            void addToWindow(iWindow* window);
            void removeFromWindow();
            void setParent(iWidget* widget);
            void removeParent();
            
            void show() { _isVisible = true; }
            void hide() { _isVisible = false; }
            
            void setSize(int width, int height) { _width = width, _height = height; };
            void setPosistion(int X, int Y) { _posX = X, _posY = Y; };
            void setScaleRestraints(int minWidth, int minHeight, int maxWidth, int maxHeight) { _sizeRestraints.minWidth = minWidth; _sizeRestraints.minHeight = minHeight; _sizeRestraints.maxWidth = maxWidth; _sizeRestraints.maxHeight = maxHeight; };
            void setPosRestraints(int minX, int minY, int maxX, int maxY) { _sizeRestraints.minX = minX; _sizeRestraints.minY = minY; _sizeRestraints.maxX = maxX; _sizeRestraints.maxY = maxY; };
            
            // Returns
            iWindow* getWindow() const { return _hostWindow; }
            iWidget* getParent() const { return _hostParent; }
            
            bool isVisible() const { return _isVisible; }
            
            int getPosX() const { return _posX; };
            int getPosY() const { return _posY; }
            int getWidth() const { return _width; }
            int getHeight() const { return _height; }
        };
    }
}

#endif /*_GOOSEUI_IWIDGET_H_*/