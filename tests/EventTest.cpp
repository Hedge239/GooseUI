#include "GooseUI/graphics/font/font.h"
#include "GooseUI/graphics/text.h"
#include "GooseUI/widgets/base/window.h"
#include "GooseUI/widgets/buttons/boxButton.h"
#include "GooseUI/GooseUI.h"

int main()
{
    goose::widgets::base::window* ExampleWindow;
    goose::widgets::buttons::boxButton* ExampleButton;

    //goose::widgets::base::window* ExampleWindow2;
    //goose::widgets::buttons::boxButton* ExampleButton2;

    goose::core::event::dispatcher evtDispatch;

    // Create The Window
    ExampleWindow = goose::widgets::base::createWindow(
        "ExampleWindow",
        400, 600,
        goose::core::enumerations::SCREEN_CENTER,
        goose::core::enumerations::opengl
    );

    /*ExampleWindow2 = goose::widgets::base::createWindow(
        "ExampleWindow2",
        400, 600,
        goose::core::enumerations::SCREEN_LEFT,
        goose::core::enumerations::opengl
    );*/

    // Create Widgets
    ExampleButton = goose::widgets::buttons::createBoxButton(
        ExampleWindow,
        1, 
        evtDispatch, 
        goose::core::enumerations::SCALE_ALL,
        goose::core::enumerations::ALIGN_LEFT | goose::core::enumerations::ALIGN_RIGHT | goose::core::enumerations::ALIGN_BOTTOM | goose::core::enumerations::ALIGN_TOP,
        100, 100, 
        50, 50
    );
    
    /*ExampleButton2 = goose::widgets::buttons::createBoxButton(
        ExampleWindow2,
        2, 
        evtDispatch, 
        goose::core::enumerations::SCALE_ALL,
        goose::core::enumerations::ALIGN_LEFT | goose::core::enumerations::ALIGN_RIGHT | goose::core::enumerations::ALIGN_BOTTOM | goose::core::enumerations::ALIGN_TOP,
        200,200, 
        50, 50
    );*/
    
    // Create Events
    evtDispatch.add(1, [&](goose::core::event::event evt){
        printf(" -- Button Clicked! ID:%i \n", ExampleButton->getEventID());
    });

    /*evtDispatch.add(2, [&](goose::core::event::event evt){
        printf(" -- Button Clicked! ID:%i \n", ExampleButton2->getEventID());
    });*/

    // Attached Widgets to window
    ExampleWindow->addWidget(ExampleButton);
    //ExampleWindow2->addWidget(ExampleButton2);

    // Cofigure Windows
    ExampleWindow->setHeader("ExampleWindow", true, true, true, true);
    ExampleWindow->isResizeable(true);

    //ExampleWindow2->setHeader("ExampleWindow", true, true, true, true);
    //ExampleWindow2->isResizeable(true);

    ExampleWindow->show();
    //ExampleWindow2->show();

    // Start loop
    goose::core::eventloop::run({ ExampleWindow});
}