#ifndef _GOOSEUI_ATLAS_H_
#define _GOOSEUI_ATLAS_H_

#include <cstdint>
#include <vector>

namespace GooseUI
{
    namespace font
    {
        class atlas
        {
            int _width, _height;
            int _x, _y, _rowHeight;
            int _colorChannel;
            unsigned int _id;

            bool _uploaded = false;
            std::vector<uint8_t> _pixels;

            public:
            atlas(int width = 1024, int height = 1024, int channels = 1);
            ~atlas();

            bool addGlyphData(int width, int height, int padding, const uint8_t* data, float& u0, float& u1, float& v0, float& v1);

            void uploaded();
            void setid(unsigned int id);

            // Returns
            std::vector<uint8_t>& getPixels();
            unsigned int getId();
            bool isUploaded();
            int getWidth();
            int getHeight();
            int getColorChannels();
        };
    }
}

#endif /*_GOOSEUI_ATLAS_H_*/