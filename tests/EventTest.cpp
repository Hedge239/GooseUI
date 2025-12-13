#include "GooseUI/GooseUI.h"
#include "GooseUI/core/enumerations.h"
#include "GooseUI/core/eventDispatcher.h"
#include "GooseUI/widgets/base/window.h"
#include "GooseUI/widgets/buttons/boxButton.h"
#include "GooseUI/widgets/display/panel.h"
#include "GooseUI/widgets/display/label.h"

int main()
{
    goose::core::event::dispatcher dispatch;
    
    goose::widgets::base::window* window1;
    goose::widgets::base::window* window2;
    
    goose::widgets::buttons::boxButton* button1;
    
    goose::widgets::display::panel* panel1;
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
        500, 500,
        goose::core::enumerations::SCREEN_CENTER,
        goose::core::enumerations::opengl
    );
    
    button1 = goose::widgets::buttons::createBoxButton(
        window1, 
        1, dispatch, 
        goose::core::enumerations::SCALE_ALL, 
        goose::core::enumerations::ALIGN_LEFT | goose::core::enumerations::ALIGN_RIGHT | goose::core::enumerations::ALIGN_BOTTOM | goose::core::enumerations::ALIGN_TOP, 
        100, 100, 
        100, 50
    );
    
    panel1 = goose::widgets::display::createPanel(
        window2, 
        goose::core::enumerations::SCALE_ALL, 
        goose::core::enumerations::ALIGN_LEFT | goose::core::enumerations::ALIGN_RIGHT | goose::core::enumerations::ALIGN_BOTTOM | goose::core::enumerations::ALIGN_TOP, 
        100, 100, 
        100, 100
    );
    
    label1 = goose::widgets ::display::createLabel(
        window2, 
        goose::core::enumerations::SCALE_NONE, 
        goose::core::enumerations::ALIGN_LEFT | goose::core::enumerations::ALIGN_RIGHT | goose::core::enumerations::ALIGN_BOTTOM | goose::core::enumerations::ALIGN_TOP, 
        150, 150, 
        100, 50
    );
    
    button1->setFont("C:/WINDOWS/FONTS/ARIAL.TTF", 12);
    button1->setLabel("Button Label :3", { 0.0f, 0.0f, 0.0f, 1.0f });
    
    label1->setFont("C:/WINDOWS/FONTS/ARIAL.TTF", 12);
    label1->setText("Hi mom!");
    
    window1->addWidget(button1);
    window2->addWidget(panel1);
    
    panel1->addChild(label1);

    window1->setHeader("Example Window 1", true, true, true, true);
    window1->isResizeable(true);
    window2->setHeader("Example Window 2", true, true, true, true);
    window2->isResizeable(true);
    
    window1->show();
    window2->show();
    
    goose::core::eventloop::run({window1, window2});
}
