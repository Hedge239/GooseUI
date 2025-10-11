#ifndef _GOOSEUI_FONTATLAS_H_
#define _GOOSEUI_FONTATLAS_H_

#include <cstdint>
#include <vector>

namespace goose
{
    namespace graphics
    {
        namespace font
        {
            class atlas
            {
                int _width, _height;
                int _Xpos, _Ypos, _rowHeight;
                unsigned int _ID;

                bool _uploaded = false;

                std::vector<uint8_t> _pixels;

                public:
                atlas(int width = 1024, int height = 1024);
                ~atlas();

                void uploaded();
                void setID(unsigned int ID);
                bool addNewBitmap(int width, int height, const uint8_t* data, float& u0, float& u1, float& v0, float& v1);

                std::vector<uint8_t>& getPixels();
                unsigned int getID();
                bool isUploaded();
                int getWidth();
                int getHeight();
            };
        }
    }
}

#endif /*_GOOSEUI_FONTATLAS_H_*/