#ifndef _ZX11_WINDOW_H_
#define _ZX11_WINDOW_H_

#include "ZephyrUI/zWidget/zWindow.h"
#include <X11/X.h>
#include <X11/Xlib.h>

namespace zUI
{
    namespace zPlatform
    {
        namespace zX11
        {
            class zX11_zWindow : public zWidget::zWindow
            {
                Display* _display;
                Window _window;

                public:
                zX11_zWindow(const std::string& title, zUI::zCore::zEnumerations::zWindowPos windowPos, int width, int height);
                virtual ~zX11_zWindow();

                Display* getDisplay();
                Window getWindow();

                // OVERIDES //
                void setTitle(const std::string& title) override;
                void setSize(int width, int height) override;

                int getPosX() override;
                int getPosY() override;
                int getWidth() override;
                int getHeight() override;

                void show() override;
                void hide() override;
                void destroy() override;

                void draw() override;
                void HandelEvents() override;
            };
        }
    }
}

#endif /*_ZX11_WINDOW_H_*/