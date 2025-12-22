#ifndef _GOOSEUI_WINDOW_H_
#define _GOOSEUI_WINDOW_H_

#include "GooseUI/core/types.h"

#include <string>

namespace goose
{
    namespace widgets
    {
        namespace base
        {
            interface::iWindow* createWindow(
                const std::string& title,
                int width, int height,
                core::types::windowPosistion posistion,
                core::types::graphicsBackend graphicsBackend
            );
        }
    }
}

#endif /*_GOOSEUI_WINDOW_H_*/