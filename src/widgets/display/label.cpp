#include "GooseUI/widgets/display/label.h"
#include "GooseUI/widgets/base/text.h"

#include "GooseUI/graphics/font/font.h"
#include "GooseUI/graphics/layoutCalculator.h"


namespace goose::widgets::display
{
    label::label(widgets::base::window* window, core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
        : _host(window), _scaleMethod(componentScaleing), _alignment(componentAlign), _posX(X), _posY(Y), _width(Width), _height(Height)
        {
            _isVisible = true;
            _color = { 0.0f, 0.0f, 0.0f, 1.0f };
            
            graphics::layout::calculator::getInitalOffsets(_initalBounds, window->getWidth(), window->getHeight(), _posX, _posY, _width, _height);
        }
        
        label* createLabel(widgets::base::window* window, core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
            { return new label(window, componentScaleing, componentAlign, X, Y, Width, Height); }
    
    // Widget Specific
    void label::setFont(const std::string& fontFilePath, int size){ if(_font == nullptr){ if(_font == nullptr){ _font = goose::graphics::font::createFont(); } _font->load(fontFilePath, size); }}
    void label::setText(const std::string& label){ _label = label; }
    void label::setColor(core::templates::renderBase::color color){ _color = color; }
    
    // overides
    // Core Functions
    void label::draw(core::templates::renderBase::renderer& renderer)
    {
        if(!_isVisible && _font == nullptr){ return; }
        graphics::layout::calculator::calculateLayout(_scaleMethod, _alignment, _sizeRestraints, _initalBounds, _host->getWidth(), _host->getHeight(), _posX, _posY, _width, _height);
        
        widgets::base::text::draw(renderer, _font.get(), _label, _posX, _posY, _color);
    }

    void label::handelEvent(core::event::event evtData){}

    // Visibility
    void label::show() { _isVisible = true; }
    void label::hide() { _isVisible = false; }

    // Posistioning
    void label::setSize(int width, int height) { _width = width; _height = height;}
    void label::setSizeRestraints(int minWidth, int minHeight, int maxWidth, int maxHeight) { _sizeRestraints.minWidth = minWidth; _sizeRestraints.minHeight = minHeight; _sizeRestraints.maxWidth = maxWidth; _sizeRestraints.maxHeight = maxHeight; }
    void label::setPosistion(int X, int Y) { _posX = X; _posY = Y; }

    // Returns
    int label::getEventID() { return -1; }
    int label::getX() { return _posX; }
    int label::getY() { return _posY; }
    int label::getWidth() { return _width; }
    int label::getHeight() { return _height; }
}