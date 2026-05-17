#ifndef _GOOSEUI_FONTMANAGER_H_
#define _GOOSEUI_FONTMANAGER_H_

#include <string>
#include <unordered_map>

#include "GooseUI/font/fontData.h"

namespace GooseUI
{
    namespace absractions
    {
        class iFont; // FORWARD DECLERATION
    }
    
    namespace font
    { 
        class manager
        {
            manager() = default;
            std::unordered_map<std::string, absractions::iFont*> _fonts;

            public:
            static manager& instance();
            absractions::iFont* getFont(const std::string& path, type fontType, int size);
        };
    }
}

#endif /*_GOOSEUI_FONTMANAGER_H_*/