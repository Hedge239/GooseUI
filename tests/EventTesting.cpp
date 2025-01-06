#include "ZephyrUI/zWidget/zWindow.h"
#include "ZephyrUI/zWidget/zButton.h"

#include "ZephyrUI/zCore/zEventDispatcher.h"

#include <iostream>

int main()
{
    zUI::zCore::zEventDispatcher EvtDispatch;

    zUI::zWidget::zWindow* TestWindow = zUI::zWidget::createWindow("EventTesting", 400, 500);
    zUI::zWidget::zButton* Button1 = zUI::zWidget::createButton(TestWindow, 1, 10, 10, 50, 50, EvtDispatch);
    zUI::zWidget::zButton* Button2 = zUI::zWidget::createButton(TestWindow, 2, 60, 60, 50, 50, EvtDispatch);

    EvtDispatch.add(1, [](zUI::zCore::zEvent event) {
        std::cout << "Lmao" << std::endl;
    });

    EvtDispatch.add(2, [](zUI::zCore::zEvent event) {
        std::cout << "Lmao2" << std::endl;
    });

    TestWindow->show();
    TestWindow->HandelEvents();
}