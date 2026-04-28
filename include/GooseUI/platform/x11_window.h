#ifndef _GOOSEUI_X11_WINDOW_H_
#define _GOOSEUI_X11_WINDOW_H_

#include "GooseUI/context.h"

#include "GooseUI/abstractions/iWindow.h"
#include "GooseUI/abstractions/iRenderer.h"
#include "GooseUI/abstractions/iWidget.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/*
    This is what I use for testing, I have no clue how it acts on other systems:
    Desktop: KDE
    Server: Through xWayland
*/

namespace GooseUI
{
    namespace platform
    {
        class x11_window : public absractions::iWindow
        {
            Display* _display = nullptr;
            ::Window _window;

            Atom _wm_delete_window;
            
            void _gl_createContext();
            void _gl_shareContext();
            void _gl_destoryContext();
            void _vk_createContext();
            void _vk_shareContext();
            
            void _startRenderFrame();
            void _endRenderFrame();

            public:
            x11_window(const std::string& title, int width, int height, screenPosistion posistion);
            virtual ~x11_window();

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
            void addWidgetToVector(absractions::iWidget* widget) override;
            void removeWidgetFromVector(absractions::iWidget* widget) override;
            void renderWidgets() override;
            void handelEvents() override;

            // Reuturns
            displayService getDisplayService() const override;
            int getWidth() override;
            int getHeight() override;
        };
    }
}

#endif /*_GOOSEUI_X11_WINDOW_H_*/