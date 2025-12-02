#include "GooseUI/GooseUI.h"
#include "GooseUI/core/enumerations.h"
#include "GooseUI/widgets/base/window.h"
#include "GooseUI/widgets/buttons/boxButton.h"
#include "GooseUI/widgets/display/label.h"

int main()
{
    goose::widgets::base::window* window1;
    goose::widgets::base::window* window2;
    
    goose::widgets::display::label* label1;
    
    // Create Windows
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
    
    // Create Labels
    label1 = goose::widgets::display::createLabel(
        window1,
        goose::core::enumerations::SCALE_ALL,
        goose::core::enumerations::ALIGN_LEFT | goose::core::enumerations::ALIGN_RIGHT | goose::core::enumerations::ALIGN_BOTTOM | goose::core::enumerations::ALIGN_TOP,
        100,
        100,
        12,
        100
    );
    
    label1->setFont("C:\\WINDOWS\\FONTS\\ARIAL.TTF", 12);
    label1->setText("JUMPING ZEBRAS VEX QUIRKY FROGS WHILE BAKING CRAZY ÉCLAIRS!");
    
    window1->addWidget(label1);
    
    window1->setHeader("Example Window 1", true, true, true, true);
    window1->isResizeable(true);
    window2->setHeader("Example Window 2", true, true, true, true);
    window2->isResizeable(true);
    
    window1->show();
    window2->show();
    
    goose::core::eventloop::run({window1, window2});
}
