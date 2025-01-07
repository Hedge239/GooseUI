#ifndef _WIN32API_WINDOW_H_
#define _WIN32API_WINDOW_H_

#include <windows.h>
#include "ZephyrUI/zWidget/zWindow.h"

namespace zUI
{
    namespace zPlatform
    {
        namespace Win32API
        {
            class Win32API_Window : public zWidget::zWindow
            {
                HWND _hwnd;
                HINSTANCE _hInstance;

                protected:
                static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

                public:
                Win32API_Window(const std::string& title, zUI::zCore::zEnumerations::zWindowPos windowPos, int width, int height);
                virtual ~Win32API_Window();

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

#endif /*_WIN32API_WINDOW_H_*/