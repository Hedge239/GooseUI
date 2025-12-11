#include "GooseUI/platform/unix/unix_freeType.h"

/* Were so back, aaand yes it manditory for me to have asci art here :3
⣿⡿⣿⣻⣿⢿⣿⣿⠃⠀⠐⣰⡟⠀⣴⠋⠁⠀⠀⠀⠀⠀⣠⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡄⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠹⣆⠀⠈⠌⢿⣿⣿⣿⣿
⣿⣽⡷⣿⡽⣿⣾⡟⠀⠠⢰⣿⣣⠞⠁⠀⠀⠀⠀⠀⣠⣺⡟⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣯⡐⠀⠈⢿⣿⣿⣿
⣿⣳⣿⢯⣿⣿⡿⠁⢀⢁⣿⡿⠃⠀⠀⠀⢀⡠⣔⢾⣵⠋⠀⣸⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡀⠀⠀⠀⣿⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀⣄⠀⠈⢧⠀⠀⠈⣿⣿⣿
⣿⣟⣾⣿⣿⣿⠃⠀⠌⣾⠏⢀⢀⣠⣔⡲⣝⡺⣵⡟⠁⠀⠄⢼⣷⣃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⡀⠀⠀⣿⠀⠙⢷⣤⡀⠀⠀⠀⠀⠀⠘⣧⠀⠘⣇⠀⠀⠘⣿⣿
⣿⣿⣿⣿⣿⠇⠀⠈⢰⣷⠺⣭⡛⢶⢎⡳⣽⡾⠋⢀⠠⢁⡄⢺⣷⢣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⡇⣿⠠⡀⠂⠹⣿⡵⣄⠠⠀⡀⠀⣿⠀⠀⢹⡄⠀⠀⠹⣿
⣿⣿⣿⡿⠃⠀⢀⠃⣿⢧⣛⢶⡹⣋⣾⡿⠋⠀⡀⠂⡤⣥⢠⢹⣷⢫⡵⠀⠀⠀⣀⣼⣧⠀⠀⠀⠀⠀⠀⢸⡇⠀⢀⠁⣿⠀⠈⠢⢀⠈⢻⣮⢳⣄⠀⠁⣿⡗⠀⢸⣇⡀⠀⠀⠸
⣿⣿⣿⡀⠀⠀⠈⣸⡟⢮⣱⣯⣾⣟⣉⣀⣶⣀⡤⠋⣰⠏⠈⠌⣿⣣⣝⡳⣆⢾⡿⢻⡞⣦⠀⠀⠀⠀⠀⢸⡇⠀⠈⣼⡟⠀⠀⠀⢱⣄⠀⡙⣿⡜⣧⡀⡟⡇⠁⣞⡿⠀⠈⠁⠀
⣿⡿⣿⣧⠀⠀⢆⣿⣽⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣿⣷⢎⣵⣾⠏⠀⠘⣿⢬⢧⡀⠀⠀⠀⣸⡇⠀⢰⣻⠇⠀⠀⢠⡞⠀⢆⣠⡜⢿⣵⣋⢿⡇⡸⢎⣿⠀⠀⠀⠀
⣿⡿⣿⣿⡇⢸⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣼⣿⣧⠀⠀⠀⢿⡟⣜⣇⠀⠀⠀⣿⠀⢀⣧⣿⣿⣿⣼⣿⣿⣿⣿⣿⣿⣿⣿⡜⣿⣧⢻⣻⡿⠀⠀⠀⠀
⣿⠿⠛⠁⠀⠀⡾⠁⠀⠀⠀⠀⠀⠀⣼⠿⣭⠻⡝⣯⣛⢟⡻⢿⣿⠛⠿⠿⣿⣧⠀⠀⠘⣿⠼⡜⣧⢄⠀⡿⢠⡞⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣼⡷⣋⣾⡏⠀⠀⠀⠀
⠋⠀⠀⠀⠀⣠⡇⠀⠀⠀⠀⠀⠀⢰⠿⠻⣖⢯⡹⢖⡭⡞⣭⢳⢿⡄⠀⠀⠀⠀⠀⠀⠀⠹⣿⣙⠶⣋⣾⣗⣏⣾⣿⣛⡟⢯⡻⡝⣯⠻⡽⣷⠈⠉⠉⠹⣿⡷⣭⣿⠁⠀⢸⡇⠀
⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⣿⠌⡡⣟⡲⢽⣿⣚⡵⣣⠩⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠹⣯⢯⠵⣿⣳⣾⣿⠧⢷⣚⢧⣯⢵⣣⡿⠵⣻⡇⠀⠀⠀⣿⣷⣿⡹⠀⠀⠸⡇⠀
⡄⠀⠀⠀⠀⢸⠁⠀⠀⠀⠀⠀⢸⡏⢢⠡⡷⣩⢿⣿⡜⢶⡙⡄⣻⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣽⣿⠟⢱⡷⢈⡾⣙⢮⣿⣚⠶⡇⢢⢹⡆⠀⠀⠀⣿⣿⣧⣛⡇⠀⠀⡟⠳
⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⢸⡇⢢⠑⣯⠵⣺⡷⣭⢳⠇⡐⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠁⠀⢸⡇⡂⡿⣍⢾⣷⡹⣚⡧⢁⢾⡃⠀⠀⠀⣿⣿⡷⣭⠇⠀⠀⡇⠀
⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠘⣷⢂⡉⢷⣫⢝⡳⢎⡟⢠⣹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠔⡿⣜⣻⣷⡹⣽⢀⢃⣾⠃⠀⠀⠀⢹⣿⣿⣜⡃⠀⠀⣷⠀
⡅⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠹⣧⢈⠌⡳⢮⡽⠋⡄⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⠐⡸⣧⡝⣣⠷⣍⠢⣸⠟⠀⠀⠀⠀⠸⣿⣿⢎⡇⠀⠀⣿⡆
⠆⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠙⢷⣌⡐⠢⢄⣣⣴⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣆⠡⢌⡙⢓⠋⡄⣲⠟⠀⠀⠀⠀⠀⠀⣿⣿⡟⡆⠀⠀⡇⢳
⠇⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠄⠀⠀⠉⠛⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⡄⠀⠀⠀⠀⠙⢶⣦⣈⣢⣵⡾⠋⠀⠀⠀⠀⠀⠀⠀⢹⣿⡿⡅⠀⠰⡇⠈
⢧⠀⠀⠀⠀⢻⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⢿⣷⡃⠀⢠⣧⠀
⣫⠄⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⢸⣷⡇⠀⢸⣯⢣
⣧⢇⠀⠀⠀⠈⣧⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⣿⠃⠀⣼⡷⢫
⣿⣚⡆⠀⠀⠀⢿⣀⠐⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⠀⠀⣿⡹⢧
⣿⡼⣹⡀⠀⠀⢸⡟⠳⣦⣄⡁⠢⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢷⣀⠀⠀⠀⠀⢀⣠⡴⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣿⡧⠀⢸⣯⡝⣣
⣽⣿⣱⢳⡀⠀⠘⣷⠀⠀⠉⠛⠶⣦⣬⣐⣀⣀⣠⣤⣤⣄⣀⡀⠀⠀⠀⠀⠙⠷⣤⡴⠞⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣴⢾⣻⣿⣿⠇⠀⣾⣳⣚⡵
⡎⣿⣧⣯⣵⠀⠀⢹⡄⠀⠀⠀⠀⠀⠀⢩⡟⠋⠀⠀⠀⠀⠀⠙⢳⣤⠀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⡞⠛⠉⠙⠛⣶⣤⣤⣴⣶⣾⢻⡟⣿⢹⡎⢳⣾⣿⣿⠀⢸⡏⠙⠛⠛
⢿⣹⣷⣎⡳⢧⡀⠸⣇⠠⠀⠀⠀⠀⠀⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣿⣷⣶⣶⣶⣶⣶⣶⣶⣶⡞⠁⠀⠀⠀⠀⠀⠀⠙⢿⣱⢫⣜⡣⢿⣏⣗⢺⣣⡿⣿⡇⢠⡟⠀⠀⠀⠀
⠈⢹⣿⣷⣏⡳⣝⣄⢻⡀⠀⠀⢄⠀⠐⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡷⢫⡝⢿⢻⡻⣝⢫⢽⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣣⠮⣝⣿⡽⣬⣷⠟⢰⣿⢇⡾⠁⠀⠀⠀⠀
⠳⣾⠁⠉⠛⢷⣯⣼⣛⣷⠀⠀⠀⠰⠈⣿⡀⠀⠠⠀⠀⠀⠀⠀⡀⠄⢨⡟⢧⡚⢧⢣⢳⢬⢣⢿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠄⣿⡵⣛⣾⣷⡿⠛⣧⠀⢸⣿⠟⠁⠀⠀⠀⠀⠀
⠀⠹⣆⡀⠀⠸⣏⠈⠉⣙⣃⡀⠀⠁⣰⠟⠳⣤⡀⠀⠀⠀⠀⠀⠀⣠⣾⣭⣅⣉⣈⣁⣁⣈⣡⣬⣿⣄⠂⠀⠀⠀⠀⠀⠁⠀⣠⣿⠞⠑⠋⠁⠀⠀⢸⠆⠈⠋⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠈⣿⠛⠶⠿⢦⣄⣀⣀⣠⡴⣻⠏⠀⠀⠀⠉⠛⠳⠶⢶⣾⣿⣿⣿⣿⢿⣿⡿⣿⣿⣿⣿⢿⣿⣿⣿⠶⠶⠦⠀⠀⠀⠂⠹⣇⠀⠀⠀⠀⠀⢀⣾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⢠⡏⠀⠀⠀⠀⠈⠉⠉⠉⣰⣏⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣾⣽⣿⣾⣽⣳⣟⣾⣽⣯⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⢻⣄⠀⡀⢀⣠⣾⢻⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⣾⠀⠀⠀⠀⠀⠀⠀⠀⠀⣯⢻⡀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⣸⣧⣿⠙⠋⠁⠀⠀⠈⢹⠀⠀⠀⠀⠀⠀⠀⠀
⠀⣰⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣌⠳⢦⣀⣀⠀⠀⣰⣿⣿⣽⣾⣯⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣻⣯⣿⣿⣦⣄⣀⣀⣀⣠⡼⣻⢧⣿⠀⠀⠀⠀⣀⣤⣼⣤⣄⠀⠀⠀⠀⠀⠀
*/

namespace goose::platform::gUnix
{
    gUnix_FreeType::gUnix_FreeType()
    {
        if(FT_Init_FreeType(&_library)){ printf("GooseUI: Faild to init FreeType \n"); }
    }

    bool gUnix_FreeType::load(const std::string& path, int pixelSize)
    {
        _size = (float)pixelSize;
        
        if(FT_New_Face(_library, path.c_str(), 0, &_face)){ printf("GooseUI: Faild to load font: %s \n", path.c_str()); return false; }
        if(FT_Set_Pixel_Sizes(_face, 0, pixelSize) != 0)
        {
            FT_Done_Face(_face);
            _face = nullptr;
            return false;
        }

        _initialized = true;
        return true;
    }

    const graphics::font::glyph& gUnix_FreeType::getGlyph(uint32_t codepoint)
    {
        if(!_initialized){ printf("GooseUI: Font not Loaded before use \n"); static graphics::font::glyph empty{}; return empty; }

        std::unordered_map<uint32_t, graphics::font::glyph>::iterator iterator = _glyphs.find(codepoint);
        if(iterator != _glyphs.end()) { return iterator->second; }

        // Map point to index and laod and rasterize -_-
        FT_UInt index = FT_Get_Char_Index(_face, codepoint);
        if(index == 0){ index = FT_Get_Char_Index(_face, '?'); }

        if(FT_Load_Glyph(_face, index, FT_LOAD_DEFAULT) != 0){ static graphics::font::glyph empty{}; return empty; }
        if(FT_Render_Glyph(_face->glyph, FT_RENDER_MODE_NORMAL) != 0){ static graphics::font::glyph empty{}; return empty; }

        FT_GlyphSlot glyphSlot = _face->glyph;
        FT_Bitmap& bitmap = glyphSlot->bitmap;

        // Handel space
        if(bitmap.width == 0 || bitmap.rows == 0)
        {
            graphics::font::glyph t_glyph;
            t_glyph.u0 = t_glyph.u1 = t_glyph.v0 = t_glyph.v1 = 0.0f;
            t_glyph.width  = 0.0f;
            t_glyph.height = 0.0f;

            t_glyph.xAdvance = (float)glyphSlot->advance.x / 64.f;
            t_glyph.xOffset  = (float)glyphSlot->bitmap_left;
            t_glyph.yOffset  = (float)glyphSlot->bitmap_top;

            _glyphs[codepoint] = t_glyph;
            return _glyphs[codepoint];
        }

        // Grayscale buffer
        std::vector<unsigned char> bitmap_grayScale(bitmap.width * bitmap.rows);
        for (int y = 0; y < bitmap.rows; ++y){ memcpy(bitmap_grayScale.data() + y * bitmap.width, bitmap.buffer + (bitmap.rows - 1 - y) * bitmap.pitch, bitmap.width); }
        
        float u0, u1, v0, v1;
        _atlas.addNewBitmap(bitmap.width, bitmap.rows, bitmap_grayScale.data(), u0, u1, v0, v1);

        // Cache Glyph
        graphics::font::glyph t_glyph;
        t_glyph.u0 = u0;
        t_glyph.u1 = u1;
        t_glyph.v0 = v0;
        t_glyph.v1 = v1;
        t_glyph.width = (float)bitmap.width;
        t_glyph.height = (float)bitmap.rows;
        t_glyph.xAdvance = (float)glyphSlot->advance.x / 64.0f;
        t_glyph.xOffset = (float)glyphSlot->bitmap_left;
        t_glyph.yOffset = (float)glyphSlot->bitmap_top - (float)glyphSlot->bitmap.rows;

        _glyphs[codepoint] = t_glyph;
        return _glyphs[codepoint];
    }

    graphics::font::atlas* gUnix_FreeType::getAtlas(){ return &_atlas; }
}