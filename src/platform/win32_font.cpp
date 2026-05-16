#include "GooseUI/platform/win32_font.h"

#include "GooseUI/context.h"


namespace GooseUI::platform // Private
{
}

namespace GooseUI::platform // Public
{
    win32_font::win32_font()
    {
        if(application::getFontFactory() == nullptr){ return; }
        Microsoft::WRL::ComPtr<IDWriteFactory> factory;
        
        HRESULT hResult = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &factory);
        if(FAILED(hResult)) { printf("GooseUI: Faild to create DirectWriteFactory \n"); }

        application::setFontFactory(reinterpret_cast<void*>(factory.Get()));
    }

    bool win32_font::load(const std::string &PathToFont, const font::fontData &fontData)
    {
        _initilized = false;
        IDWriteFactory* pFactory = reinterpret_cast<IDWriteFactory*>(application::getFontFactory());
        if(pFactory == nullptr){ printf("GooseUI: Faild to get DirectWriteFactory \n"); return false; }

        _fontData = fontData;

        // DPI
        HDC screen = GetDC(nullptr);
        int DPIx = GetDeviceCaps(screen, LOGPIXELSX);
        ReleaseDC(nullptr, screen);
        
        float scale = (DPIx / 96.0f) + 1;
        _fontData.size = fontData.size * scale;

        // Load font
        HRESULT hResult = pFactory->CreateFontFileReference(std::wstring(PathToFont.begin(), PathToFont.end()).c_str(), nullptr, &_fontFile);
        if(FAILED(hResult)) { printf("GooseUI: Faild to load Font: %s \n", PathToFont.c_str()); return false; }

        // Analyze - I did me research >:3
        BOOL supported = false; 
        UINT32 numberOfFaces;
        DWRITE_FONT_FILE_TYPE fileType;
        DWRITE_FONT_FACE_TYPE faceType;

        _fontFile->Analyze(&supported, &fileType, &faceType, &numberOfFaces);
        if(!supported) { return false; }

        hResult = pFactory->CreateFontFace(faceType, 1, _fontFile.GetAddressOf(), 0, DWRITE_FONT_SIMULATIONS_NONE, &_face);
        if(FAILED(hResult)) { return false; }
        
        _initilized = true;
        return true;
    }

    const font::glyph& win32_font::getGlyph(uint32_t codepoint)
    {
        
    }

    font::atlas* getAtlas()
    {
        
    }
}