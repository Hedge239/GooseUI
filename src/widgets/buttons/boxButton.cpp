#include "GooseUI/widgets/buttons/boxButton.h"
#include "GooseUI/widgets/base/text.h"

#include "GooseUI/graphics/font/font.h"
#include "GooseUI/graphics/layoutCalculator.h"


namespace goose::widgets::buttons
{
    // Create NEW widget and set private variables
    boxButton::boxButton(int eventID, goose::core::event::dispatcher& evtDispatcher, core::types::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
        : _eventID(eventID), _evtDispatcher(evtDispatcher)
        {
            _scaleing = componentScaleing;
            _alignment = componentAlign;
            _posX = X;
            _posY = Y;
            _width = Width;
            _height = Height;
            
            _isVisible = true; 
            _isPressed = false;
            _outlineSize = 1; 
            _color = { 0.85f, 0.85f, 0.85f, 1.0f };
        }

    boxButton* createBoxButton(int eventID, goose::core::event::dispatcher& evtDispatcher, core::types::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
        { return new boxButton(eventID, evtDispatcher, componentScaleing, componentAlign, X, Y, Width, Height); }

    // Widget Specific Functions
    void boxButton::setFont(const std::string& fontFilePath, int size){ if(_font == nullptr){ _font = goose::graphics::font::createFont(); } _font->load(fontFilePath, size); }   
    void boxButton::setLabel(const std::string& text, const core::types::color& color){ _label = text; _labelColor = color; }
    void boxButton::setOutlineSize(int size) { _outlineSize = size; }
    void boxButton::setColor(const core::types::color& color){ _color = color;}
    
    // overides
    // Core Functions
    void boxButton::draw(interface::iRenderer& renderer)
    {
        _preDraw();
        
        if(!_isPressed) { renderer.drawRect(_posX - _outlineSize, _posY - _outlineSize, _width + 2 * _outlineSize, _height + 2 * _outlineSize, { 0.0f, 0.0f, 0.0f, 1.0f }); }
        renderer.drawRect(_posX, _posY, _width, _height, _color);
        
        if(_label != "" && _font != nullptr)
        { 
            int textWidth, textHeight;
            float textScale;
            
            widgets::base::text::getSize(_font.get(), _label, 1, textWidth, textHeight);
            graphics::layout::calculator::calculateTextLayout(_width, _height, textScale, textWidth, textHeight);
            
            widgets::base::text::draw(renderer, _font.get(), _label, _posX + (_width  - textWidth) / 2, _posY + (_height + textHeight) / 2, textScale, _labelColor); 
        }
    }

    void boxButton::pollEvent(core::types::event::eventData evtData)
    {
        if(evtData.type == core::types::event::eventType::leftMouseDown && evtData.mouseX >= _posX && evtData.mouseX <= _posX + _width && evtData.mouseY >= _posY && evtData.mouseY <= _posY + _height)
            { _evtDispatcher.dispatch(_eventID, evtData); _isPressed = true; }

        if(evtData.type == core::types::event::eventType::leftMouseUp && _isPressed == true) { _isPressed = false; }
    }
}