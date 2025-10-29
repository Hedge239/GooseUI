#ifndef _GOOSEUI_WIN32_WINDOW_H_
#define _GOOSEUI_WIN32_WINDOW_H_

#include "GooseUI/widgets/base/window.h"
#include "GooseUI/graphics/context.h"
#include "GooseUI/core/templates/renderBase.h"
#include "GooseUI/core/event.h"

#include <windows.h>
#include <cstdio>
#include <vector>

namespace goose
{
    namespace platform
    {
        namespace gWin32
        {
            class gWin32_window : public widgets::base::window
            {
                HWND _hwnd;
                HINSTANCE _hInstance;

                goose::core::templates::renderBase::color _bgColor;
                goose::core::templates::renderBase::renderer* _backend;
                goose::core::enumerations::graphicsBackend _backendContext;

                std::vector<core::templates::widget::base*> _widgets;
                bool _isRunning;

                void _createContext_openGL();
                void _shareContext_openGL();
                void _destroyContext_openGL();
                void _createContext_vulkan();
                void _destroyContext_vulkan();

                protected:
                static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

                public:
                gWin32_window(const std::string& title, int width, int height, goose::core::enumerations::windowPos posistion, goose::core::enumerations::graphicsBackend graphicsBacken);
                virtual ~gWin32_window();

                HWND getHwnd();

                // Overides
                // Window Configuration
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
                void addWidget(core::templates::widget::base* widget) override;
                void renderWidgets() override;
                void handelEvents() override;

                // Reuturns
                bool isRunning() override;
                int getDisplayService() const override;
                int getWidth() override;
                int getHeight() override;
            };
        }
    }
}

#endif /*_GOOSEUI_WIN32_WINDOW_H_*/