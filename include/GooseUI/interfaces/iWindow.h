#ifndef _GOOSEUI_IWINDOW_H_
#define _GOOSEUI_IWINDOW_H_

#include "GooseUI/core/types.h"

#include <string>
#include <vector>

namespace goose
{
    namespace interface
    {
        class iWidget;      // FORWARD DECLERATION
        class iRenderer;    // FORWARD DECLERATION
        
        class iWindow
        {
            protected:
            iRenderer* _backend = nullptr;
            std::vector<iWidget*> _widgets;
            
            core::types::color _bgColor;
            core::types::graphicsBackend _context;
            
            bool _running;
            
            public:
            virtual ~iWindow() = default;

            // Window Configuration
            virtual void setWindowIcon(const std::string& icon) = 0; // To Simplify I will only accept .ico for icons on all platforms
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
            virtual bool isRunning() const { return _running; };
            
            virtual int getDisplayService() const = 0;
            virtual int getWidth() = 0;
            virtual int getHeight() = 0;
        };
    }
}

#endif /*_GOOSEUI_IWINDOW_H_*/