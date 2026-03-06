#ifndef _GOOSEUI_WINDOW_H_
#define _GOOSEUI_WINDOW_H_

#include "GooseUI/types.h"

#include <string>

namespace GooseUI
{
    namespace widgets
    {
        absractions::iWindow* createWindow(
            const std::string& title,
            int width, int height,
            screenPosistion posistion
        );
    }
}

#endif /*_GOOSEUI_WINDOW_H_*/