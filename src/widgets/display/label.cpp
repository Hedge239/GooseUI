#include "GooseUI/widgets/display/label.h"
#include "GooseUI/widgets/base/text.h"

#include "GooseUI/graphics/font/font.h"
#include "GooseUI/graphics/layoutCalculator.h"


namespace goose::widgets::display
{
    label::label(core::types::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
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
        
        label* createLabel(core::types::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
            { return new label(componentScaleing, componentAlign, X, Y, Width, Height); }
    
    // Widget Specific
    void label::setFont(const std::string& fontFilePath, int size){ if(_font == nullptr){ if(_font == nullptr){ _font = goose::graphics::font::createFont(); } _font->load(fontFilePath, size); }}
    void label::setText(const std::string& label){ _label = label; }
    void label::setColor(const core::types::color& color){ _color = color; }
    
    // overides
    // Core Functions
    void label::draw(interface::iRenderer& renderer)
    {
        if(!_isVisible || !_hostWindow || _font == nullptr){ return; }
        if(_hostParent){ _isVisible = _hostParent->isVisible(); }
        
        const int hostWidth = _hostParent ? _hostParent->getWidth() : _hostWindow->getWidth(); const int hostHeight = _hostParent ? _hostParent->getHeight() : _hostWindow->getHeight();
        graphics::layout::calculator::calculateLayout(_scaleing, _alignment, _sizeRestraints, _initalBounds, hostWidth, hostHeight, _posX, _posY, _width, _height);
        
        widgets::base::text::draw(renderer, _font.get(), _label, _posX, _posY, 1, _color);
    }

    void label::pollEvent(core::types::event::eventData evtData){ return; }
}