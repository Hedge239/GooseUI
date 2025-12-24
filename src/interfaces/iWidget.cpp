#include "GooseUI/interfaces/iWidget.h"
#include "GooseUI/interfaces/iWindow.h"

#include "GooseUI/graphics/layoutCalculator.h"

namespace goose::interface
{
    // Parent Window
    void iWidget::addToWindow(iWindow* window)
    {
        if(!window || _hostParent){ return; }
        
        _hostWindow = window;
        _hostWindow->addWidgetToVector(this);
        
        graphics::layout::calculator::getInitalOffsets(
            _initalBounds, 
            _hostWindow->getWidth(), 
            _hostWindow->getHeight(), 
            _posX, _posY, 
            _width, _height
        );
    }
    
    void iWidget::removeFromWindow()
    {
        if(!_hostWindow || _hostParent){ return; }
        
        _hostWindow->removeWidgetFromVector(this);
        _hostWindow = nullptr;
    }
    
    // Parent Widget
    void iWidget::setParent(iWidget* widget)
    {
        if(!widget || _hostWindow){ return; }
        
        _hostParent = widget; _hostWindow = _hostParent->getWindow();
        _hostWindow->addWidgetToVector(this);
        
        _sizeRestraints.minX = _hostParent->getPosX();
        _sizeRestraints.minY = _hostParent->getPosY();
        
        graphics::layout::calculator::getInitalOffsets(
            _initalBounds, 
            _hostParent->getWidth(), 
            _hostParent->getHeight(), 
            _posX + _sizeRestraints.minX, 
            _posY + _sizeRestraints.minY, 
            _width, _height
        );
    }
    
    void iWidget::removeParent()
    {
        if(!_hostParent){ return; }
        
        _hostWindow->removeWidgetFromVector(this);
        
        _hostWindow = nullptr; 
        _hostParent = nullptr;
        
        _sizeRestraints.minX = 0;
        _sizeRestraints.minY = 0;
    }
}