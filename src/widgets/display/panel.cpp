#include "GooseUI/widgets/display/panel.h"
#include "GooseUI/graphics/layoutCalculator.h"

#include <algorithm>


namespace goose::widgets::display
{
    panel::panel(widgets::base::window* window, core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
        : _host(window), _scaleMethod(componentScaleing), _alignment(componentAlign), _posX(X), _posY(Y), _width(Width), _height(Height)
        {
            _isVisible = true;
            _color = { 0.85f, 0.85f, 0.85f, 1.0f };
            
            graphics::layout::calculator::getInitalOffsets(_initalBounds, window->getWidth(), window->getHeight(), _posX, _posY, _width, _height);
        }
    
        panel* createPanel(widgets::base::window* window, core::enumerations::componentScale componentScaleing, int componentAlign, int X, int Y, int Width, int Height)
            { return new panel(window, componentScaleing, componentAlign, X, Y, Width, Height); }
            
        // Widget Specific
        void panel::addChild(core::templates::widget::base* widget){ _widgets.push_back(widget); _host->addWidget(widget); }
        void panel::removeChild(core::templates::widget::base* widget)
        {
            std::vector<core::templates::widget::base*>::iterator target = std::find(_widgets.begin(), _widgets.end(), widget);
            if(target != _widgets.end()){ _widgets.erase(target); _host->removeWidget(widget); }
        }
        
        void panel::setColor(core::templates::renderBase::color color){ _color = color; }
        
        // overides
        void panel::draw(core::templates::renderBase::renderer& renderer)
        {
            if(!_isVisible) { return; }
            graphics::layout::calculator::calculateLayout(_scaleMethod, _alignment, _sizeRestraints, _initalBounds, _host->getWidth(), _host->getHeight(), _posX, _posY, _width, _height);
            
            renderer.drawRect(_posX, _posY, _width, _height, _color);
        }
        
        void panel::handelEvent(core::event::event evtData){}
    
        // Visibility
        void panel::show() 
        { 
            _isVisible = true;
            
            if(_widgets.empty()){ return; }
            for(core::templates::widget::base* widget : _widgets)
            {
                if(widget)
                {
                    widget->show();
                }
            } 
        }
        void panel::hide() 
        { 
            _isVisible = false; 
            
            if(_widgets.empty()){ return; }
            for(core::templates::widget::base* widget : _widgets)
            {
                if(widget)
                {
                    widget->hide();
                }
            } 
        }
    
        // Posistioning
        void panel::setSize(int width, int height) { _width = width; _height = height;}
        void panel::setSizeRestraints(int minWidth, int minHeight, int maxWidth, int maxHeight) { _sizeRestraints.minWidth = minWidth; _sizeRestraints.minHeight = minHeight; _sizeRestraints.maxWidth = maxWidth; _sizeRestraints.maxHeight = maxHeight; }
        void panel::setPosistion(int X, int Y) { _posX = X; _posY = Y; }
    
        // Returns
        int panel::getEventID() { return -1; }
        int panel::getX() { return _posX; }
        int panel::getY() { return _posY; }
        int panel::getWidth() { return _width; }
        int panel::getHeight() { return _height; }
}