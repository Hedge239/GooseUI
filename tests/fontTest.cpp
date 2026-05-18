#include "GooseUI/GooseUI.h"

#include "GooseUI/abstractions/iWindow.h"
#include "GooseUI/abstractions/iFont.h"

#include "GooseUI/events/eventLoop.h"

#include "GooseUI/widgets/label.h"

GooseUI::absractions::iWindow* _window;
GooseUI::absractions::iFont* _font;
GooseUI::widgets::label* _label;

int main()
{
    GooseUI::application::init(GooseUI::application::backendType::OpenGL);

    _window = GooseUI::absractions::createWindow("Window One", 500, 500, GooseUI::SCREEN_CENTER);
    _window->isResizeable(true);
    _window->setHeader("GooseUI Window", true, true, true, true);

    // Font Data
    GooseUI::font::fontData fontData;
    fontData.size = 12;

    // Label
    _label = GooseUI::widgets::createLable(
        GooseUI::SCALE_ALL, 
        GooseUI::ALIGN_TOP | GooseUI::ALIGN_BOTTOM | GooseUI::ALIGN_LEFT | GooseUI::ALIGN_RIGHT,
        200, 200,
        20, 20
    );

    _label->setFont("C:/WINDOWS/FONTS/ARIAL.TTF", fontData);
    _label->setText("Hello World");
    _label->addToWindow(_window);
    
    _window->show();
    GooseUI::event::loop::run({_window});
}