#ifndef _GOOSEUI_FONTMANAGER_H_
#define _GOOSEUI_FONTMANAGER_H_

#include <memory>
#include <string>
#include <unordered_map>

namespace goose
{
    namespace graphics
    {
        namespace font
        {
            class font; // FORWARD DECLERATION - I feel like I am spelling this worse every time

            class manager
            {
                manager() = default;
                std::unordered_map<std::string, std::unique_ptr<font>> _fonts;

                public:
                static manager& instance();

                font* getFont(const std::string& path, int pixelSize);
            };
        }
    }
}

#endif /*_GOOSEUI_FONTMANAGER_H_*/