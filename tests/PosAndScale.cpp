#include "ZephyrUI/zWidget/zWindow.h"
#include "ZephyrUI/zWidget/zButton.h"
#include "ZephyrUI/zCore/zEventDispatcher.h"

#include <iostream>

#define evtID_TOPLEFT 1
#define evtID_TOPRIGHT 2
#define evtID_BOTTOMLEFT 3
#define evtID_BOTTOMRIGHT 4
#define evtID_RIGHT 5
#define evtID_LEFT 6 
#define evtID_TOP 7
#define evtID_BOTTOM 8 
#define evtID_CENTER 9

// Note the widget is allways 15 off?!
// So if you wanted the most right assumeing the window is 600x600
// The math would be 600 - width - 15 why idk, might just like auto calc this ya kown

int main()
{

    zUI::zCore::zEventDispatcher EvtDispatch;

    zUI::zWidget::zWindow* MainWindow = zUI::zWidget::createWindow("Posistion and Scale Test", zUI::zCore::zEnumerations::SCREEN_CENTER, 600, 600);

    // TopLeft
    zUI::zWidget::zButton* TopLeft = zUI::zWidget::createButton(MainWindow, evtID_TOPLEFT, zUI::zCore::zEnumerations::SCALE_NONE, zUI::zCore::zEnumerations::ALIGN_LEFT | zUI::zCore::zEnumerations::ALIGN_TOP, 10, 10, 80, 25, EvtDispatch);
    TopLeft->setLabel("TopLeft");

    EvtDispatch.add(evtID_TOPLEFT, [](zUI::zCore::zEvent event) {
        std::cout << "TopLeft" << std::endl;
    });

    // TopRight
    zUI::zWidget::zButton* TopRight = zUI::zWidget::createButton(MainWindow, evtID_TOPRIGHT, zUI::zCore::zEnumerations::SCALE_NONE, zUI::zCore::zEnumerations::ALIGN_TOP | zUI::zCore::zEnumerations::ALIGN_RIGHT, 495, 10, 80, 25, EvtDispatch);
    TopRight->setLabel("TopRight");

    EvtDispatch.add(evtID_TOPRIGHT, [](zUI::zCore::zEvent event) {
        std::cout << "TopRight" << std::endl;
    });

    // Top
    zUI::zWidget::zButton* Top = zUI::zWidget::createButton(MainWindow, evtID_TOP, zUI::zCore::zEnumerations::SCALE_NONE, zUI::zCore::zEnumerations::ALIGN_TOP | zUI::zCore::zEnumerations::ALIGN_RIGHT | zUI::zCore::zEnumerations::ALIGN_LEFT, 252, 10, 80, 25, EvtDispatch);
    Top->setLabel("Top");

    EvtDispatch.add(evtID_TOP, [](zUI::zCore::zEvent event) {
        std::cout << "Top" << std::endl;
    });

    // Bottom
    zUI::zWidget::zButton* Bottom = zUI::zWidget::createButton(MainWindow, evtID_BOTTOM, zUI::zCore::zEnumerations::SCALE_NONE, zUI::zCore::zEnumerations::ALIGN_BOTTOM | zUI::zCore::zEnumerations::ALIGN_RIGHT | zUI::zCore::zEnumerations::ALIGN_LEFT, 252, 545, 80, 25, EvtDispatch);
    Bottom->setLabel("Bottom");

    EvtDispatch.add(evtID_BOTTOM, [](zUI::zCore::zEvent event) {
        std::cout << "Bottom" << std::endl;
    });

    // Left
    zUI::zWidget::zButton* left = zUI::zWidget::createButton(MainWindow, evtID_LEFT, zUI::zCore::zEnumerations::SCALE_NONE, zUI::zCore::zEnumerations::ALIGN_LEFT | zUI::zCore::zEnumerations::ALIGN_TOP | zUI::zCore::zEnumerations::ALIGN_BOTTOM, 10, 267, 80, 25, EvtDispatch);
    left->setLabel("left");

    EvtDispatch.add(evtID_LEFT, [](zUI::zCore::zEvent event) {
        std::cout << "left" << std::endl;
    });

    // Right
    zUI::zWidget::zButton* right = zUI::zWidget::createButton(MainWindow, evtID_RIGHT, zUI::zCore::zEnumerations::SCALE_NONE, zUI::zCore::zEnumerations::ALIGN_RIGHT | zUI::zCore::zEnumerations::ALIGN_TOP | zUI::zCore::zEnumerations::ALIGN_BOTTOM, 495, 267, 80, 25, EvtDispatch);
    right->setLabel("right");

    EvtDispatch.add(evtID_RIGHT, [](zUI::zCore::zEvent event) {
        std::cout << "right" << std::endl;
    });

    // Bottomleft
    zUI::zWidget::zButton* Bottomleft = zUI::zWidget::createButton(MainWindow, evtID_BOTTOMLEFT, zUI::zCore::zEnumerations::SCALE_NONE, zUI::zCore::zEnumerations::ALIGN_LEFT | zUI::zCore::zEnumerations::ALIGN_BOTTOM, 10, 545, 80, 25, EvtDispatch);
    Bottomleft->setLabel("Bottomleft");

    EvtDispatch.add(evtID_BOTTOMLEFT, [](zUI::zCore::zEvent event) {
        std::cout << "Bottomleft" << std::endl;
    });

    // BottomRight
    zUI::zWidget::zButton* BottomRight = zUI::zWidget::createButton(MainWindow, evtID_BOTTOMRIGHT, zUI::zCore::zEnumerations::SCALE_NONE, zUI::zCore::zEnumerations::ALIGN_RIGHT | zUI::zCore::zEnumerations::ALIGN_BOTTOM, 495, 545, 80, 25, EvtDispatch);
    BottomRight->setLabel("BottomRight");

    EvtDispatch.add(evtID_BOTTOMRIGHT, [](zUI::zCore::zEvent event) {
        std::cout << "BottomRight" << std::endl;
    });

    // ALL
    zUI::zWidget::zButton* center = zUI::zWidget::createButton(MainWindow, evtID_CENTER, zUI::zCore::zEnumerations::SCALE_ALL, zUI::zCore::zEnumerations::ALIGN_RIGHT | zUI::zCore::zEnumerations::ALIGN_BOTTOM | zUI::zCore::zEnumerations::ALIGN_LEFT | zUI::zCore::zEnumerations::ALIGN_TOP, 252, 267, 80, 25, EvtDispatch);
    center->setLabel("Center");

    EvtDispatch.add(evtID_CENTER, [](zUI::zCore::zEvent event) {
        std::cout << "Center" << std::endl;
    });

    MainWindow->show();
    MainWindow->HandelEvents();
}