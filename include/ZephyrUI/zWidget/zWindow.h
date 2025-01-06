#ifndef _ZWINDOW_H_
#define _ZWINDOW_H_

#include <string>

namespace zUI
{
    namespace zWidget
    {
        class zWindow
        {
            public:
            virtual ~zWindow() = default;

            // Events
            virtual void setTitle(const std::string& title) = 0;
            virtual void setSize(int width, int height) = 0;

            virtual void show() = 0;
            virtual void hide() = 0;
            virtual void destroy() = 0;

            // Returns
            virtual int getPosX() = 0;
            virtual int getPosY() = 0;
            virtual int getWidth() = 0;
            virtual int getHeight() = 0;

            // Backend
            virtual void draw() = 0;
            virtual void HandelEvents() = 0;
        };

        zWindow* createWindow(std::string title, int width, int height); // TODO: WindowPos
    }
}

#endif /*_ZWINDOW_H_*/