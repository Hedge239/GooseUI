#include "ZephyrUI/zWidget/zWindow.h"
#include "ZephyrUI/zWidget/zButton.h"

#include "ZephyrUI/zCore/zEventDispatcher.h"

#include <iostream>

int main()
{
    zUI::zCore::zEventDispatcher EvtDispatch;

    zUI::zWidget::zWindow* TestWindow = zUI::zWidget::createWindow("EventTesting", 400, 500);
    zUI::zWidget::zButton* Button1 = zUI::zWidget::createButton(TestWindow, 10, 10, 50, 50, EvtDispatch);

    EvtDispatch.add(zUI::zCore::zEventType::ButtonPress, [](zUI::zCore::zEvent event) {
        std::cout << "Lmao" << std::endl;
    });

    TestWindow->show();
    TestWindow->HandelEvents();
}