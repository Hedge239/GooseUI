#include "GooseUI/widgets/buttons/boxButton.h"
#include "GooseUI/core/templates/renderBase.h"
#include "GooseUI/graphics/font/font.h"
#include "GooseUI/graphics/text.h"
std::unique_ptr<goose::graphics::font::font> arial; //TMP
namespace goose::widgets::buttons
{
    // Create NEW widget and set private variables
    boxButton::boxButton(widgets::base::window* window, int eventID, goose::core::event::dispatcher& evtDispatcher, goose::core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
        : _host(window), _eventID(eventID), _evtDispatcher(evtDispatcher), _scaleMethod(componentScaleing), _alignment(componentAlign), _posX(X), _posY(Y), _width(Width), _height(Height) { _isVisible = true; _isPressed = false; _outlineSize = 1; _color = { 0.85f, 0.85f, 0.85f, 1.0f }; 
        arial = goose::graphics::font::createFont(); //TMP
        arial->load("ARIAL.TTF", 12);//TMP
    }

    boxButton* createBoxButton(widgets::base::window* window, int eventID, goose::core::event::dispatcher& evtDispatcher, goose::core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
        { return new boxButton(window, eventID, evtDispatcher, componentScaleing, componentAlign, X, Y, Width, Height); }

    // Widget Specific Functions
    void boxButton::setLabel(std::string label) { _label = label; }
    void boxButton::setOutlineSize(int size) { _outlineSize = size; }
    
    // overides
    // Core Functions
    void boxButton::draw(core::templates::renderBase::renderer& renderer)
    {
        if(!_isVisible) { return; }

        //if(!_isPressed) { renderer.drawRect(_posX - _outlineSize, _posY - _outlineSize, _width + 2 * _outlineSize, _height + 2 * _outlineSize, { 0.0f, 0.0f, 0.0f, 1.0f }); }
        //renderer.drawRect(_posX, _posY, _width, _height, _color);
        graphics::text::draw(renderer, arial.get(), "Hello World", _posX, _posY, { 0.0f, 0.0f, 0.0f, 1.0f }); //TMP
    }

    void boxButton::handelEvent(core::event::event evtData)
    {
        if(evtData.type == core::event::eventType::leftMouseDown && evtData.mouseX >= _posX && evtData.mouseX <= _posX + _width && evtData.mouseY >= _posY && evtData.mouseY <= _posY + _height)
            { _evtDispatcher.dispatch(_eventID, evtData); _isPressed = true; }

        if(evtData.type == core::event::eventType::leftMouseUp && _isPressed == true) { _isPressed = false; }
    }

    // Visibility
    void boxButton::show() { _isVisible = true; }
    void boxButton::hide() { _isVisible = false; }

    // Posistioning
    void boxButton::setSize(int width, int height) { _width = width; _height = height;}
    void boxButton::setPosistion(int X, int Y) { _posX = X; _posY = Y; }

    // Returns
    int boxButton::getEventID() { return _eventID; }
    int boxButton::getX() { return _posX; }
    int boxButton::getY() { return _posY; }
    int boxButton::getWidth() { return _width; }
    int boxButton::getHeight() { return _height; }
}