#include "GooseUI/GooseUI.h"

#include "GooseUI/abstractions/iWindow.h"

#include "GooseUI/events/eventLoop.h"

#include "GooseUI/widgets/boxButton.h"


GooseUI::absractions::iWindow* _window;
GooseUI::widgets::boxButton* _button;

GooseUI::event::dispatcher _evtDispatch;

int main()
{
    GooseUI::application::init(GooseUI::application::backendType::OpenGL);

    _window = GooseUI::absractions::createWindow("Window One", 500, 500, GooseUI::SCREEN_CENTER);
    _window->isResizeable(true);
    _window->setHeader("GooseUI Window", true, true, true, true);

    // Button
    _button = GooseUI::widgets::createBoxButton(
        1,
        _evtDispatch,
        GooseUI::SCALE_NONE, 
        GooseUI::ALIGN_TOP | GooseUI::ALIGN_BOTTOM | GooseUI::ALIGN_LEFT | GooseUI::ALIGN_RIGHT,
        20, 20,
        10, 10
    );

    _evtDispatch.add(1, [&](GooseUI::event::data evt){
        printf("[Window1 Evt] [ID: 1] - Input Detected \n");
    });

    _button->addToWindow(_window);

    _window->show();
    GooseUI::event::loop::run({_window});
}