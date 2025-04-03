#include "ZephyrUI/zPlatform/x11/zX11_zWindow.h"

using namespace zUI;
using namespace zPlatform;
using namespace zX11;

zX11_zWindow::zX11_zWindow(const std::string& title, zUI::zCore::zEnumerations::zWindowPos windowPos, int width, int height)
{
}

zX11_zWindow::~zX11_zWindow()
{
    XDestroyWindow(_display, _window);
    XCloseDisplay(_display);
}

// Window Settings
void zX11_zWindow::setTitle(const std::string& title) {}
void zX11_zWindow::setSize(int width, int height) {}

// Returns
int zX11_zWindow::getPosX() {return 0;}
int zX11_zWindow::getPosY() {return 0;}
int zX11_zWindow::getWidth() {return 0;}
int zX11_zWindow::getHeight() {return 0;}

// Window Management
void zX11_zWindow::show() {}

void zX11_zWindow::hide() {}
void zX11_zWindow::destroy() {}
void zX11_zWindow::draw() {}

void zX11_zWindow::HandelEvents()
{
}