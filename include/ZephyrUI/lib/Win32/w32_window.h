#ifndef _W32_WINDOW_H_
#define _W32_WINDOW_H_

#include "ZephyrUI/zWindow.h"

namespace zephyr
{
    namespace lib
    {
        void w32_CreateWindow(zephyr::zWindowConfig winCfg);
        void w32_CloseWindow();
    }
}

#endif /*_W32_WINDOW_H_*/