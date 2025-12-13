#ifndef _GOOSEUI_WINDOW_H_
#define _GOOSEUI_WINDOW_H_

#include "GooseUI/core/enumerations.h"
#include "GooseUI/core/templates/widgetBase.h"

#include <string>

namespace goose
{
    namespace widgets
    {
        namespace base
        {
            class window
            {
                public:
                virtual ~window() = default;

                // Window Configuration
                virtual void setHeader(const std::string& title, bool isVisible, bool hasButtons, bool hasMinimize, bool hasMaximise) = 0;
                
                virtual void isResizeable(bool isResizeable) = 0;
                virtual void isAllwaysOnTop(bool isOnTop) = 0;

                // Window Size
                virtual void setSize(int width, int height) = 0;
                
                virtual void maximize() = 0;
                virtual void minimize() = 0;
                virtual void restoreSize() = 0;

                // Window Visibility
                virtual void show() = 0;
                virtual void hide() = 0;
                virtual void destroy() = 0;

                // Widget Management
                virtual void addWidget(core::templates::widget::base* widget) = 0;
                virtual void removeWidget(core::templates::widget::base* widget) = 0;
                virtual void renderWidgets() = 0;
                virtual void handelEvents() = 0;

                // Reuturns
                virtual bool isRunning() = 0;
                
                virtual int getDisplayService() const = 0;
                virtual int getWidth() = 0;
                virtual int getHeight() = 0;
            };

            window* createWindow(
                const std::string& title,
                int width, int height,
                goose::core::enumerations::windowPos posistion,
                goose::core::enumerations::graphicsBackend graphicsBackend
            );
        }
    }
}

#endif /*_GOOSEUI_WINDOW_H_*/