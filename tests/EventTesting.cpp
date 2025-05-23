#include "ZephyrUI/zWidget/zWindow.h"
#include "ZephyrUI/zWidget/zButton.h"

#include "ZephyrUI/zCore/zEventDispatcher.h"

#include <iostream>


zUI::zWidget::zWindow* g_TestWindow;

void changeWindowTitle(std::string title) {g_TestWindow->setTitle(title);}

int main()
{
    zUI::zCore::zEventDispatcher EvtDispatch;

    g_TestWindow = zUI::zWidget::createWindow("EventTesting", zUI::zCore::zEnumerations::SCREEN_CENTER, 400, 500);
    zUI::zWidget::zButton* Button1 = zUI::zWidget::createButton(g_TestWindow, 1, zUI::zCore::zEnumerations::SCALE_ALL, zUI::zCore::zEnumerations::ALIGN_LEFT | zUI::zCore::zEnumerations::ALIGN_RIGHT | zUI::zCore::zEnumerations::ALIGN_BOTTOM | zUI::zCore::zEnumerations::ALIGN_TOP, 10, 10, 50, 50, EvtDispatch);
    zUI::zWidget::zButton* Button2 = zUI::zWidget::createButton(g_TestWindow, 2, zUI::zCore::zEnumerations::SCALE_ALL, zUI::zCore::zEnumerations::ALIGN_LEFT | zUI::zCore::zEnumerations::ALIGN_RIGHT | zUI::zCore::zEnumerations::ALIGN_BOTTOM | zUI::zCore::zEnumerations::ALIGN_TOP, 60, 60, 50, 50, EvtDispatch);

    EvtDispatch.add(1, [](zUI::zCore::zEvent event) {
       std::cout << "ID: 1" << std::endl;
       changeWindowTitle("UwU :3");
    });

    //Button1->setLabel("test");
    
    EvtDispatch.add(2, [](zUI::zCore::zEvent event) {
        //std::string text = std::any_cast<std::string>(event.data.at("text")); - Need to figure a way to prevent a out_of_range error
        std::cout << "ID: 2" << std::endl;
        changeWindowTitle("OwO :3");
    });

    g_TestWindow->show();
    g_TestWindow->HandelEvents();
}