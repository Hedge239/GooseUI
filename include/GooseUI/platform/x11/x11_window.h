#ifndef _GOOSEUI_X11_WINDOW_H_
#define _GOOSEUI_X11_WINDOW_H_

#include "GooseUI/graphics/context.h"

#include "GooseUI/interfaces/iWindow.h"
#include "GooseUI/interfaces/iWidget.h"
#include "GooseUI/interfaces/iRenderer.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace goose
{
    namespace platform
    {
        namespace gX11
        {
            class gX11_window : public interface::iWindow
            {
                Display* _display = nullptr;
                ::Window _window;

                Atom _wm_delete_window;
                
                void _gl_createContext();
                void _gl_shareContext();
                void _gl_destoryContext();
                void _vk_createContext();
                void _vk_shareContext();

                public:
                gX11_window(const std::string& title, int width, int height, core::types::windowPosistion posistion, core::types::graphicsBackend graphicsBackend);
                virtual ~gX11_window();

                ::Window getWindow();
                Display* getDisplay();

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
                void addWidgetToVector(interface::iWidget* widget) override;
                void removeWidgetFromVector(interface::iWidget* widget) override;
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

#endif /*_GOOSEUI_X11_WINDOW_H_*/