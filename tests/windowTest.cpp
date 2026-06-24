#include "GooseUI/GooseUI.h"

#include "GooseUI/abstractions/iWindow.h"
#include "GooseUI/events/eventLoop.h"

/*
    The first window WILL ALLWAYS be the parent window, if it is closed all other windows will close and the loop will end
    I could eventually add a way to stop this, but honestly I dont want to, the the bug is a feature now
*/

GooseUI::absractions::iWindow* _window1;
GooseUI::absractions::iWindow* _window2;

int main()
{
    GooseUI::application::init(GooseUI::application::backendType::OpenGL);
    
    _window1 = GooseUI::absractions::createWindow("Window One", 500, 500, GooseUI::SCREEN_BOTTOM_LEFT);
    _window1->isResizeable(true);
    _window1->setHeader("Window One", true, true, true, true);
    _window1->show();
    GooseUI::event::loop::add(_window1);
    
    _window2 = GooseUI::absractions::createWindow("Window Two", 100, 200, GooseUI::SCREEN_TOP_RIGHT);
    _window2->isResizeable(true);
    _window2->setHeader("Window Two", true, true, true, true);
    _window2->show();
    GooseUI::event::loop::add(_window2);

    GooseUI::event::loop::run();
}