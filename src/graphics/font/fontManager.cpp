#include "GooseUI/graphics/font/fontManager.h"
#include "GooseUI/graphics/font/font.h"


namespace goose::graphics::font
{
    manager& manager::instance()
    {
        static manager instance;
        return instance;
    }

    font* manager::getFont(const std::string& path, int pixelSize)
    {
        std::string key = path + "_" + std::to_string(pixelSize);

        std::unordered_map<std::string, std::unique_ptr<font>>::iterator iterator = _fonts.find(key);
        if(iterator != _fonts.end()) { return iterator->second.get(); }

        std::unique_ptr<font> font = createFont();
        if(!font->load(path, pixelSize)) { return nullptr; }

        _fonts[key] = std::move(font);
        return _fonts[key].get();
    }
}