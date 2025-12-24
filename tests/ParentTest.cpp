#include "GooseUI/GooseUI.h"

#include "GooseUI/widgets/containers/panel.h"
#include "GooseUI/widgets/base/window.h"

int main()
{
    goose::interface::iWindow* window1;
    
    goose::widgets::containers::panel* panel1;
    goose::widgets::containers::panel* panel2;
    
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
        200, 200, 
        20, 20
    );
    
    panel2->setColor({1, 0, 0, 1});
    
    panel1->addToWindow(window1);
    panel2->setParent(panel1);
    
    window1->show();
    goose::core::eventloop::run({window1});
}