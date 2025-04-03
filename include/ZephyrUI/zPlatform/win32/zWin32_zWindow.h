#ifndef _ZWIN32_ZWINDOW_H_
#define _ZWIN32_ZWINDOW_H_

#include "ZephyrUI/zWidget/zWindow.h"
#include <windows.h>

namespace zUI
{
    namespace zPlatform
    {
        namespace zWin32
        {
            class zWin32_zWindow : public zWidget::zWindow
            {
                HWND _hwnd;
                HINSTANCE _hInstance;

                protected:
                static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

                public:
                zWin32_zWindow(const std::string& title, zUI::zCore::zEnumerations::zWindowPos windowPos, int width, int height);
                virtual ~zWin32_zWindow();

                HWND getHwnd();

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

#endif /*_ZWIN32_ZWINDOW_H_*/