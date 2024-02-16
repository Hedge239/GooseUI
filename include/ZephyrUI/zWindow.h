#ifndef _ZWINDOW_H_
#define _ZWINDOW_H_

#include <string>

namespace zephyr
{
    struct zWindowConfig
    {
        std::string className;
        std::string displayTitle;

        int displayHeight;
        int displayWidth;

        bool disableResize;
        bool disableMinimizeToggle;
        bool disableMaximizeToggle;
        bool disableToolBar;

        // Default Values
        zWindowConfig() :
            displayTitle("ZephyrUI Window"),
            displayHeight(500),
            displayWidth(500)
        {}
    };
    
    class zWindow
    {
        private:
            zWindowConfig _WindowConfig;

        public:
            zWindow();
            zWindow(zWindowConfig windowCfg);

            void create();
            void close();
    };

    namespace WindowManager
    {
        void RemoveWindowFromMap(std::string className);
    }

    void CreateWindow(zWindowConfig zWindowConfig);
    void CloseWindow(std::string className);
}

#endif /*_ZWINDOW_H_*/