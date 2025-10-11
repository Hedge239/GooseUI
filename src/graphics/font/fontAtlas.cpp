#include "GooseUI/graphics/font/fontAtlas.h"

#include <iostream>
#include <cstring>


namespace goose::graphics::font
{
    atlas::atlas(int width, int height) 
        : _width(width), _height(height), _Xpos(0), _Ypos(0), _rowHeight(0), _pixels(width* height, 0), _ID(0) {}
    atlas::~atlas() {}

    bool atlas::addNewBitmap(int width, int height, const uint8_t* data, float& u0, float& u1, float& v0, float& v1)
    {
        // Start new row?
        if(_Xpos + width >= _width)
        {
            _Xpos = 0;
            _Ypos += _rowHeight + 1;
            _rowHeight = 0;
        }

        // Is Atlas Full?
        if(_Ypos + height >= _height) { return false; }
        
        for(int row = 0; row < height; ++row) 
        { 
            memcpy(&_pixels[(_Ypos + row) * _width + _Xpos], &data[row * width], width);
        }

        u0 = (float)_Xpos / (float)_width;
        u1 = (float)(_Xpos + width) / (float)_width;
        v0 = (float)_Ypos / (float)_height;
        v1 = (float)(_Ypos + height) / (float)_height;

        // Update Packing Cursor
        _Xpos += width + 1;
        if(height > _rowHeight) { _rowHeight = height; }

        _uploaded = false;
        return true;
    }

    void atlas::uploaded() { _uploaded = true; }
    void atlas::setID(unsigned int ID) { _ID = ID; }

    std::vector<uint8_t>& atlas::getPixels() { return _pixels; }
    unsigned int atlas::getID() { return _ID; }
    bool atlas::isUploaded() { return _uploaded; }
    int atlas::getWidth() { return _width; }
    int atlas::getHeight() { return _height; }
}