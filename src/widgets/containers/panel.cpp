#include "GooseUI/widgets/containers/panel.h"

#include "GooseUI/graphics/layoutCalculator.h"


namespace goose::widgets::containers
{
    panel::panel(core::types::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
    {
        _scaleing = componentScaleing;
        _alignment = componentAlign;
        _posX = X;
        _posY = Y;
        _width = Width;
        _height = Height;
        
        _isVisible = true;
        _color = { 0.0f, 0.0f, 0.0f, 1.0f };
    }
    
    panel* createPanel(core::types::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
        { return new panel(componentScaleing, componentAlign, X, Y, Width, Height); }
        
        // overides
        void panel::draw(interface::iRenderer& renderer)
        {
            if(!_isVisible || !_hostWindow){ return; }
            if(_hostParent){ _isVisible = _hostParent->isVisible(); }
            
            // pain
            const int hostWidth = _hostParent ? _hostParent->getWidth() : _hostWindow->getWidth(); const int hostHeight = _hostParent ? _hostParent->getHeight() : _hostWindow->getHeight();
            graphics::layout::calculator::calculateLayout(_scaleing, _alignment, _sizeRestraints, _initalBounds, hostWidth, hostHeight, _posX, _posY, _width, _height);
            
            renderer.drawRect(_posX, _posY, _width, _height, _color);
        }
        
        void panel::pollEvent(core::types::event::eventData evtData){ return; }
        
        // If a widget has a parent, we can not add or remove it from a window unless the parent is also removed - vise vera if no parent but attached to window, cannot add parent 
        void panel::addToWindow(interface::iWindow* window)
        {
            if(!window || _hostParent){ return; }
            _hostWindow = window;
            _hostWindow->addWidgetToVector(this);
            graphics::layout::calculator::getInitalOffsets(_initalBounds, _hostWindow->getWidth(), _hostWindow->getHeight(), _posX, _posY, _width, _height);
        }
        
        void panel::removeFromWindow()
        {
            if(!_hostWindow || _hostParent){ return; }
            _hostWindow->removeWidgetFromVector(this);
            _hostWindow = nullptr;
        }
        
        void panel::setParent(iWidget* widget)
        { 
            if(!widget || _hostWindow){ return; }
            _hostParent = widget; _hostWindow = _hostParent->getWindow();
            _hostWindow->addWidgetToVector(this);
            graphics::layout::calculator::getInitalOffsets(_initalBounds, _hostParent->getWidth(), _hostParent->getHeight(), _posX, _posY, _width, _height);
        }
        
        void panel::removeParent()
        { 
            if(!_hostParent){ return; }
            _hostWindow->removeWidgetFromVector(this);
            _hostWindow = nullptr; _hostParent = nullptr; 
        }
    
        void panel::show() { _isVisible = true; }
        void panel::hide() { _isVisible = false; }
    
        void panel::setSize(int width, int height) { _width = width; _height = height;}
        void panel::setSizeRestraints(int minWidth, int minHeight, int maxWidth, int maxHeight) { _sizeRestraints.minWidth = minWidth; _sizeRestraints.minHeight = minHeight; _sizeRestraints.maxWidth = maxWidth; _sizeRestraints.maxHeight = maxHeight; }
        void panel::setPosistion(int X, int Y) { _posX = X; _posY = Y; }
}