#include "ZephyrUI/zWidget/zWindow.h"
#include "ZephyrUI/zWidget/zButton.h"

#include "ZephyrUI/zCore/zEventDispatcher.h"

#include <iostream>

int main()
{
    zUI::zCore::zEventDispatcher EvtDispatch;

    zUI::zWidget::zWindow* TestWindow = zUI::zWidget::createWindow("EventTesting", zUI::zCore::zEnumerations::SCREEN_CENTER, 400, 500);
    zUI::zWidget::zButton* Button1 = zUI::zWidget::createButton(TestWindow, 1, zUI::zCore::zEnumerations::SCALE_ALL, zUI::zCore::zEnumerations::ALIGN_LEFT | zUI::zCore::zEnumerations::ALIGN_RIGHT | zUI::zCore::zEnumerations::ALIGN_BOTTOM | zUI::zCore::zEnumerations::ALIGN_TOP, 10, 10, 50, 50, EvtDispatch);
    //zUI::zWidget::zButton* Button2 = zUI::zWidget::createButton(TestWindow, 2, 60, 60, 50, 50, EvtDispatch);

    EvtDispatch.add(1, [](zUI::zCore::zEvent event) {
        std::cout << "Lmao" << std::endl;
    });

    /*
    EvtDispatch.add(2, [](zUI::zCore::zEvent event) {
        //std::string text = std::any_cast<std::string>(event.data.at("text")); - Need to figure a way to prevent a out_of_range error
        std::cout << "Lmao2" << std::endl;
    });*/

    TestWindow->show();
    TestWindow->HandelEvents();
}