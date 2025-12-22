#include "GooseUI/GooseUI.h"

#include "GooseUI/widgets/buttons/boxButton.h"
#include "GooseUI/widgets/base/window.h"

#include <cstdio>

int main()
{
    goose::core::event::dispatcher dispatch;
    
    goose::interface::iWindow* window1;
    goose::interface::iWindow* window2;
    
    goose::widgets::buttons::boxButton* button1;
    goose::widgets::buttons::boxButton* button2;
    
    // 1st Window
    window1 = goose::widgets::base::createWindow(
        "First Window",
        500, 500,
        goose::core::types::windowPosistion::SCREEN_CENTER,
        goose::core::types::graphicsBackend::opengl
    );
    
    button1 = goose::widgets::buttons::createBoxButton(
        window1, 
        1, 
        dispatch, 
        goose::core::types::componentScale::SCALE_NONE, 
        goose::core::types::componentAlign::ALIGN_LEFT | goose::core::types::componentAlign::ALIGN_TOP | goose::core::types::componentAlign::ALIGN_RIGHT | goose::core::types::componentAlign::ALIGN_BOTTOM, 
        200, 200, 
        50, 50
    );
    
    dispatch.add(1, [&](goose::core::types::event::eventData evt){
        printf("[Window1 Evt] [ID: 1] - Input Detected \n");
    });
    
    window1->addWidget(button1);
    window1->setHeader("EventTest Window 1", true, true, true, true);
    window1->isResizeable(true);
    
    window2 = goose::widgets::base::createWindow(
        "Second Window",
        500, 500,
        goose::core::types::windowPosistion::SCREEN_CENTER,
        goose::core::types::graphicsBackend::opengl
    );
    
    button2 = goose::widgets::buttons::createBoxButton(
        window2, 
        2, 
        dispatch, 
        goose::core::types::componentScale::SCALE_ALL, 
        goose::core::types::componentAlign::ALIGN_LEFT | goose::core::types::componentAlign::ALIGN_TOP | goose::core::types::componentAlign::ALIGN_RIGHT | goose::core::types::componentAlign::ALIGN_BOTTOM, 
        200, 200, 
        50, 50
    );
    
    button2->setFont("C:/WINDOWS/FONTS/ARIAL.TTF", 12);
    button2->setLabel("Button Label :3", { 0.0f, 0.0f, 0.0f, 1.0f });
    
    dispatch.add(2, [&](goose::core::types::event::eventData evt){
        printf("[Window2 Evt] [ID: 2] - Input Detected \n");
    });
    
    window2->addWidget(button2);
    window2->setHeader("EventTest Window 2", true, true, true, true);
    window2->isResizeable(true);
    
    window1->show();
    window2->show();
    goose::core::eventloop::run({window1, window2});
}
