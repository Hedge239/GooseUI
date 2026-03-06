#ifndef _GOOSEUI_IWINDOW_H_
#define _GOOSEUI_IWINDOW_H_

#include "GooseUI/types.h"

#include <string>
#include <vector>

namespace GooseUI
{
    namespace absractions
    {
        class iWindow
        {
            protected:
            std::vector<iWidget*> _widgets;
            
            color _bgColor;
            bool _isRunning;
            
            public:
            virtual ~iWindow() = default;
            
            // Window Configuration
            virtual void setWindowIcon(const std::string& iconPath) = 0;
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

            // Widget Management - Renamed to make it harder to accidently use
            virtual void addWidgetToVector(iWidget* widget) = 0;
            virtual void removeWidgetFromVector(iWidget* widget) = 0;
            virtual void renderWidgets() = 0;
            virtual void handelEvents() = 0;

            // Reuturns
            virtual bool isRunning() const { return _isRunning; };
            
            virtual displayService getDisplayService() const = 0;
            virtual int getWidth() = 0;
            virtual int getHeight() = 0;
        };
    }
}

#endif /*_GOOSEUI_IWINDOW_H_*/