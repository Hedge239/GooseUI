#include "GooseUI/graphics/font/font.h"

#if defined(_WIN32) // Use DirectWrite

    #include "GooseUI/platform/win32/win32_directWrite.h"
    std::unique_ptr<goose::graphics::font::font> goose::graphics::font::createFont() { return std::make_unique<goose::platform::gWin32::gWin32_DirectWrite>(); }

#else // Use Freetype
#endif