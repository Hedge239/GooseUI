#include "GooseUI/widgets/window.h"
#include "GooseUI/widgets/button.h"

#include "GooseUI/core/eventDispatcher.h"

#include "iostream"

int main()
{
    goose::widget::window* ExampleWindow;
    goose::widget::button* ExampleButton;

    goose::core::eventDispatcher evtDispatch;

    ExampleWindow = goose::widget::createWindow(
        "ExampleWindow", 
        goose::core::enumerations::SCREEN_CENTER, 
        400, 500
    );
    
    
    ExampleButton = goose::widget::createButton(
        ExampleWindow, 
        1, 
        evtDispatch, 
        goose::core::enumerations::SCALE_ALL, 
        goose::core::enumerations::ALIGN_LEFT | goose::core::enumerations::ALIGN_RIGHT | goose::core::enumerations::ALIGN_BOTTOM | goose::core::enumerations::ALIGN_TOP,
        60, 50, 
        50, 50
    );

    ExampleButton->setLabel("balls");

    evtDispatch.add(1, [&](goose::core::event::event evt){
        std::cout << "ID: 1" << std::endl;
        ExampleButton->setPosistion(100, 100);
    });
    

    ExampleWindow->show();
    ExampleWindow->handelEvents();
}