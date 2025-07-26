#ifndef _GOOSEUI_WIN32_WINDOW_H_
#define _GOOSEUI_WIN32_WINDOW_H_

#include "GooseUI/widgets/window.h"

#include <windows.h>

namespace goose
{
    namespace platform
    {
        namespace gWin32    // We will put "g" infront to prevent conflicts
        {
            class gWin32_window : public widget::window
            {
                HWND _hwnd;
                HINSTANCE _hInstance;

                protected:
                static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

                public:
                gWin32_window(const std::string& title, goose::core::enumerations::windowPos posistion, int width, int height);
                virtual ~gWin32_window();

                HWND getHwnd();

                // OVERIDES //
                void setHeader(const std::string& title, bool isVisible, bool hasButtons, bool hasMinimize, bool hasMaximise) override;
                void setSize(int width, int height) override;

                void isResizeable(bool isResizeable) override;
                void isAllwaysOnTop(bool isOnTop) override;

                void maximize() override;
                void minimize() override;
                void restoreSize() override;
                void show() override;
                void hide() override;
                void destroy() override;

                // Backend
                void handelEvents() override;

                // Returns
                int getWidth() override;
                int getHeight() override;
            };
        }
    }
}

#endif /*_GOOSEUI_WIN32_WINDOW_H_*/