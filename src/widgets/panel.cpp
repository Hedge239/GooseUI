#include "GooseUI/widgets/panel.h"

#include "GooseUI/context.h"


namespace GooseUI::widgets
{
    panel::panel(widgetScaleing widgetScaleing, int widgetAlignment, int x, int y, int width, int height)
    {
        _widgetScaleing = widgetScaleing;
        _alignment = widgetAlignment;
        _posX = x;
        _posY = y;
        _width = width;
        _height = height;

        _isVisible = true;
        _outlineSize = 0;
        _color = { 0.85f, 0.85f, 0.85f, 1.0f };
        _outlineColor = { 0.0f, 0.0f, 0.0f, 0.0f };
    }

    panel* createPanel(widgetScaleing widgetScaleing, int widgetAlignment, int x, int y, int width, int height)
        { return new panel(widgetScaleing, widgetAlignment, x, y, width, height); }

    // Widget Specific
    void panel::setColor(const color& color){ _color = color; }
    void panel::setOutlineColor(const color& color){ _outlineColor = color; }
    void panel::setOutlineSize(int size){ _outlineSize = size; }

    void panel::draw()
    {
        _preDraw();

        if(_outlineSize > 0){ application::getRenderer()->drawRect(_posX - _outlineSize, _posY - _outlineSize, _width + 2 * _outlineSize, _height + 2 * _outlineSize, _outlineColor); }
        application::getRenderer()->drawRect(_posX, _posY, _width, _height, _color);
    }

    void panel::pollEvent(event::data evtData){ return; }
}