#ifndef _GOOSEUI_X11_WINDOW_H_
#define _GOOSEUI_X11_WINDOW_H_

#include "GooseUI/widgets/base/window.h"
#include "GooseUI/graphics/context.h"
#include "GooseUI/core/templates/renderBase.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace goose
{
    namespace platform
    {
        namespace gX11
        {
            class gX11_window : public widgets::base::window
            {
                Display* _display = nullptr;
                ::Window _window;

                Atom _wm_delete_window;

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

                public:
                gX11_window(const std::string& title, int width, int height, goose::core::enumerations::windowPos posistion, goose::core::enumerations::graphicsBackend graphicsBacken);
                virtual ~gX11_window();

                ::Window getWindow();
                Display* getDisplay();

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
                void removeWidget(core::templates::widget::base* widget) override;
                void renderWidgets() override;
                void handelEvents() override;

                // Reuturns
                int getDisplayService() const override;
                bool isRunning() override;
                int getWidth() override;
                int getHeight() override;
            };
        }
    }
}

#endif /*_GOOSEUI_X11_WINDOW_H_*/