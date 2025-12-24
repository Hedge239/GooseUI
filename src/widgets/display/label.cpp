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
        graphics::layout::calculator::calculateLayout(_scaleing, _alignment, _sizeRestraints, _initalBounds, _hostWindow->getWidth(), _hostWindow->getHeight(), _posX, _posY, _width, _height);
        
        widgets::base::text::draw(renderer, _font.get(), _label, _posX, _posY, 1, _color);
    }

    void label::pollEvent(core::types::event::eventData evtData){ return; }
    
    // If a widget has a parent, we can not add or remove it from a window unless the parent is also removed - vise vera if no parent but attached to window, cannot add parent 
    void label::addToWindow(interface::iWindow* window)
    {
        if(!window || _hostParent){ return; }
        _hostWindow = window;
        _hostWindow->addWidgetToVector(this);
        graphics::layout::calculator::getInitalOffsets(_initalBounds, _hostWindow->getWidth(), _hostWindow->getHeight(), _posX, _posY, _width, _height);
    }
    
    void label::removeFromWindow()
    {
        if(!_hostWindow || _hostParent){ return; }
        _hostWindow->removeWidgetFromVector(this);
        _hostWindow = nullptr;
    }
    
    void label::setParent(iWidget* widget)
    { 
        if(!widget || _hostWindow){ return; }
        _hostParent = widget; _hostWindow = _hostParent->getWindow();
        _hostWindow->addWidgetToVector(this);
        graphics::layout::calculator::getInitalOffsets(_initalBounds, _hostParent->getWidth(), _hostParent->getHeight(), _posX, _posY, _width, _height);
    }
    
    void label::removeParent()
    { 
        if(!_hostParent){ return; }
        _hostWindow->removeWidgetFromVector(this);
        _hostWindow = nullptr; _hostParent = nullptr; 
    }

    // Visibility
    void label::show() { _isVisible = true; }
    void label::hide() { _isVisible = false; }

    // Posistioning
    void label::setSize(int width, int height) { _width = width; _height = height;}
    void label::setSizeRestraints(int minWidth, int minHeight, int maxWidth, int maxHeight) { _sizeRestraints.minWidth = minWidth; _sizeRestraints.minHeight = minHeight; _sizeRestraints.maxWidth = maxWidth; _sizeRestraints.maxHeight = maxHeight; }
    void label::setPosistion(int X, int Y) { _posX = X; _posY = Y; }
}