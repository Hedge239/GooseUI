#include "ZephyrUI/zWidget/zWindow.h"
#include "ZephyrUI/zWidget/zButton.h"
#include "ZephyrUI/zCore/zEventDispatcher.h"

#include "iostream"

#define evtID_CREATEWINDOW 1
#define evtID_CLOSEWINDOW 2

zUI::zCore::zEventDispatcher g_EvtDispatch;
zUI::zWidget::zWindow* g_SecondWindow;

bool g_secondWindowExist;

int main()
{
    zUI::zWidget::zWindow* MainWindow = zUI::zWidget::createWindow("MultiWindowTest - MainWindow", zUI::zCore::zEnumerations::SCREEN_CENTER, 600, 600);

    // Create Window
    zUI::zWidget::zButton* createWindow = zUI::zWidget::createButton(MainWindow, evtID_CREATEWINDOW, zUI::zCore::zEnumerations::SCALE_NONE, zUI::zCore::zEnumerations::ALIGN_LEFT | zUI::zCore::zEnumerations::ALIGN_TOP | zUI::zCore::zEnumerations::ALIGN_BOTTOM, 10, 267, 80, 25, g_EvtDispatch);
    createWindow->setLabel("Create Window");

    g_EvtDispatch.add(evtID_CREATEWINDOW, [](zUI::zCore::zEvent event) {
        std::cout << "Attempting to Create window" << std::endl;

        if(!g_secondWindowExist)
        {
            g_SecondWindow = zUI::zWidget::createWindow("MultiWindowTest - SecondWindow", zUI::zCore::zEnumerations::SCREEN_CENTER, 600, 600);
            g_SecondWindow->show();
            g_SecondWindow->HandelEvents();

            g_secondWindowExist = true;
        }
    });

    // Close Window
    zUI::zWidget::zButton* closeWindow = zUI::zWidget::createButton(MainWindow, evtID_CLOSEWINDOW, zUI::zCore::zEnumerations::SCALE_NONE, zUI::zCore::zEnumerations::ALIGN_RIGHT | zUI::zCore::zEnumerations::ALIGN_TOP | zUI::zCore::zEnumerations::ALIGN_BOTTOM, 495, 267, 80, 25, g_EvtDispatch);
    closeWindow->setLabel("Close Window");

    g_EvtDispatch.add(evtID_CLOSEWINDOW, [](zUI::zCore::zEvent event) {
        std::cout << "Attempting to Close window" << std::endl;

        if(g_secondWindowExist)
        {
            g_SecondWindow->destroy();
            g_secondWindowExist = false;
        }
    });

    MainWindow->show();
    MainWindow->HandelEvents();
}