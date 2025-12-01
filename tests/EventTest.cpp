#include "GooseUI/GooseUI.h"
#include "GooseUI/core/enumerations.h"
#include "GooseUI/widgets/base/window.h"
#include "GooseUI/widgets/buttons/boxButton.h"
#include "GooseUI/widgets/display/label.h"

int main()
{
    goose::widgets::base::window* window1;
    goose::widgets::base::window* window2;
    
    window1 = goose::widgets::base::createWindow(
        "Window1",
        500, 500,
        goose::core::enumerations::SCREEN_CENTER,
        goose::core::enumerations::opengl
    );
    
    window2 = goose::widgets::base::createWindow(
        "Window2",
        200, 200,
        goose::core::enumerations::SCREEN_CENTER,
        goose::core::enumerations::opengl
    );
    
    window1->setHeader("Example Window 1", true, true, true, true);
    window1->isResizeable(true);
    window2->setHeader("Example Window 2", true, true, true, true);
    window2->isResizeable(true);
    
    window1->show();
    window2->show();
    
    goose::core::eventloop::run({window1, window2});
}
