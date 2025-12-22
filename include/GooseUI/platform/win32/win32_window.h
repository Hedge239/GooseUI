#ifndef _GOOSEUI_WIN32_WINDOW_H_
#define _GOOSEUI_WIN32_WINDOW_H_

#include "GooseUI/graphics/context.h"

#include "GooseUI/interfaces/iWindow.h"
#include "GooseUI/interfaces/iWidget.h"
#include "GooseUI/interfaces/iRenderer.h"

#include <windows.h>
#include <cstdio>

#undef interface

namespace goose
{
    namespace platform
    {
        namespace gWin32
        {
            class gWin32_window : public interface::iWindow
            {
                HWND _hwnd;
                HINSTANCE _hInstance;
                
                void _gl_createContext();
                void _gl_shareContext();
                void _gl_destoryContext();
                void _vk_createContext();
                void _vk_shareContext();

                protected:
                static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

                public:
                gWin32_window(const std::string& title, int width, int height, core::types::windowPosistion posistion, core::types::graphicsBackend graphicsBackend);
                virtual ~gWin32_window();

                HWND getHwnd();

                // Overides
                // Window Configuration
                void setWindowIcon(const std::string& ICO) override;
                void setHeader(const std::string& title, bool isVisible, bool hasButtons, bool hasMinimize, bool hasMaximise) override;
                
                void isResizeable(bool isResizeable) override;
                void isAllwaysOnTop(bool isOnTop) override;

                // Window Size
                void setSize(int width, int height) override;
                
                void maximize() override;
                void minimize() override;
                void restoreSize() override;

                // Window Visibility
                void show() override;
                void hide() override;
                void destroy() override;

                // Widget Management
                void addWidget(interface::iWidget* widget) override;
                void removeWidget(interface::iWidget* widget) override;
                void renderWidgets() override;
                void handelEvents() override;

                // Reuturns
                int getDisplayService() const override;
                int getWidth() override;
                int getHeight() override;
            };
        }
    }
}

#endif /*_GOOSEUI_WIN32_WINDOW_H_*/