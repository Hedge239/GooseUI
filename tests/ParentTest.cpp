#include "GooseUI/GooseUI.h"

#include "GooseUI/widgets/containers/panel.h"
#include "GooseUI/widgets/display/label.h"
#include "GooseUI/widgets/base/window.h"

int main()
{
    goose::interface::iWindow* window1;
    
    goose::widgets::containers::panel* panel1;
    goose::widgets::containers::panel* panel2;
    
    goose::widgets::display::label* label1;
    
    window1 = goose::widgets::base::createWindow(
        "MyWindow",
        500, 500,
        goose::core::types::windowPosistion::SCREEN_CENTER,
        goose::core::types::graphicsBackend::opengl
    );
    
    window1->setHeader("ParentTest", true, true, true, true);
    window1->isResizeable(true);
    
    panel1 = goose::widgets::containers::createPanel(
        goose::core::types::componentScale::SCALE_ALL, 
        goose::core::types::componentAlign::ALIGN_LEFT | goose::core::types::componentAlign::ALIGN_TOP | goose::core::types::componentAlign::ALIGN_RIGHT | goose::core::types::componentAlign::ALIGN_BOTTOM, 
        10, 10, 
        400, 400
    );
    
    panel2 = goose::widgets::containers::createPanel(
        goose::core::types::componentScale::SCALE_NONE, 
        goose::core::types::componentAlign::ALIGN_LEFT | goose::core::types::componentAlign::ALIGN_TOP | goose::core::types::componentAlign::ALIGN_RIGHT | goose::core::types::componentAlign::ALIGN_BOTTOM, 
        10, 10, 
        200, 200
    );
    
    label1 = goose::widgets::display::createLabel(
        goose::core::types::componentScale::SCALE_NONE, 
        goose::core::types::componentAlign::ALIGN_LEFT | goose::core::types::componentAlign::ALIGN_TOP | goose::core::types::componentAlign::ALIGN_RIGHT | goose::core::types::componentAlign::ALIGN_BOTTOM, 
        0, 0, 
        20, 20
    );
    
    label1->setFont("C:/WINDOWS/FONTS/ARIAL.TTF", 12);
    label1->setText("Hi Mom! :3");
    
    panel2->setColor({1, 0, 0, 1});
    
    panel1->addToWindow(window1);
    panel2->setParent(panel1);
    label1->setParent(panel2);
    
    window1->show();
    goose::core::eventloop::run({window1});
}