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
        _color = { 0.85f, 0.85f, 0.85f, 1.0f };
    }
    
    panel* createPanel(core::types::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
        { return new panel(componentScaleing, componentAlign, X, Y, Width, Height); }
    
        
    void panel::setColor(const core::types::color& color){ _color = color; }
    
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
}