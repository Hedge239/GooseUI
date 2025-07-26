#ifndef _GOOSEUI_XORG_WINDOW_H_
#define _GOOSEUI_XORG_WINDOW_H_

#include "GooseUI/widgets/window.h"

#include <vector>
#include <X11/X.h>
#include <X11/Xlib.h>

namespace goose
{
    namespace widget
    {
        class widget_base; // FORWARD DELCERATION
    }

    namespace platform
    {
        namespace gXOrg
        {
            class gXOrg_window : public widget::window
            {
                Display* _display;
                Window _window;

                std::vector<widget::widget_base*> _children;

                public:
                gXOrg_window(const std::string& title, goose::core::enumerations::windowPos posistion, int width, int height);
                virtual ~gXOrg_window();

                Display* getDisplay();
                Window getWindow();

                void addToXEventLoop(widget::widget_base* targetWidget);

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

#endif /*_GOOSEUI_XORG_WINDOW_H_*/