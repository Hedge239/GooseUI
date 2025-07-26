#ifndef _GOOSEUI_WINDOW_H_
#define _GOOSEUI_WINDOW_H_

#include "GooseUI/core/enumerations.h"

#include <string>

namespace goose 
{
    namespace widget
    {
        class window
        {
            public:
            virtual ~window() = default;

            // Toggles
            virtual void setHeader(const std::string& title, bool isVisible, bool hasButtons, bool hasMinimize, bool hasMaximise) = 0;
            virtual void setSize(int width, int height) = 0;

            virtual void isResizeable(bool isResizeable) = 0;
            virtual void isAllwaysOnTop(bool isOnTop) = 0;

            virtual void maximize() = 0;
            virtual void minimize() = 0;
            virtual void restoreSize() = 0;
            virtual void show() = 0;
            virtual void hide() = 0;
            virtual void destroy() = 0;

            // Backend
            virtual void handelEvents() = 0;

            // Returns
            virtual int getWidth() = 0;
            virtual int getHeight() = 0;
        };

        window* createWindow(
                std::string title, 
                goose::core::enumerations::windowPos posistion, 
                int width, int height
        );
    }
}

#endif /*_GOOSEUI_WINDOW_H_*/