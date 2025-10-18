#include "GooseUI/platform/win32/win32_directWrite.h"

/*
Me after coding this:
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣿⣛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡵⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢟⣻⣭⣽⣿⣷⣿⣯⡭⢛⣻⣧⣽⣷⣶⣶⣟⣫⣴⣶⣿⣿⣿⣿⣿⣶⣯⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣱⣿⠿⠻⢿⣿⣿⣿⣉⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢟⣭⣵⣜⢿⣿⣿⠜⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣽⣆⠠⣿⢗⣎⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣮⡻⣿⣿⡗⢈⠛⢸⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡌⣵⣿⡏⠶⣹⣝⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⡫⠶⢹⣿⣿⣜⠟⢉⢮⢃⡝⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣻⣝⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠈⢃⣾⣿⣞⢿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣵⣿⡟⣼⣿⣿⣿⣿⣿⣿⢸⣿⣿⢻⣿⣿⠻⣿⢁⢿⣿⣿⣿⢸⣿⣿⣿⣿⣧⢹⣿⣿⣿⡈⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⡿⣵⣿⢫⡽⣸⣿⣿⡿⣿⣿⣿⡇⡇⣟⣡⣼⣿⣿⣤⢛⢸⢸⣿⣿⡟⢸⣿⣿⣿⣿⣿⡏⣿⣿⣿⣿⡜⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣷⣻⣿⣸⣇⣿⣿⣿⡇⢿⣿⣿⡅⣷⢻⣿⣿⣿⣿⣿⡟⣾⡏⣿⣿⡇⣸⣿⣿⣿⣿⣿⣷⢹⣿⣿⣿⣧⠹⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣷⣽⣏⢸⣿⣿⣿⢷⡆⣿⣿⠃⢿⡎⣿⣿⣿⣿⣿⠃⠿⡇⣿⣿⢹⡇⣿⣿⣿⣿⣿⣿⢸⣿⣿⣿⣿⡆⣝⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⡿⣛⠭⠈⣿⣿⣿⢸⣿⡎⠋⠀⣴⣿⡌⣿⣿⣿⡿⣴⠦⠀⠉⠃⢿⣇⣿⣿⢇⣿⣿⣿⢸⣿⣿⣿⣿⣿⢹⣞⣿⣿
⣿⣿⣿⣿⣿⣿⣿⠫⣫⣿⢵⡇⢿⢿⣿⠸⠋⡠⠀⠁⠀⠹⣿⡜⣿⣿⢱⠁⠠⠀⠃⠰⣦⡀⠙⢟⣼⣿⡿⠿⠫⢿⣿⣿⣿⣿⡎⣿⣞⣿
⣿⣿⣿⣿⣿⣿⡏⣽⣿⣿⡮⠇⣆⢘⢿⠀⣾⠇⣠⣤⣤⢄⣿⡟⢮⢣⣿⡠⣶⣶⣶⠄⢿⡅⣠⢸⡉⣒⣚⣛⠁⣿⣿⣿⣿⣿⣷⢻⣿⡞
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠇⣒⣒⠇⣥⣿⡵⠭⣭⣵⣾⣿⣥⣬⣤⣿⣿⣶⠒⡆⠾⣖⣫⣥⣬⣥⣤⣤⣜⡘⠸⣿⣿⣿⣿⣿⡎⣿⣿
⣿⣿⣿⣿⣿⡿⢟⣻⣽⣶⡾⣃⢭⣷⣮⣟⣛⠷⠶⠿⠿⠿⠿⠿⠿⠿⠿⠿⣻⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠹⣿⣿⣿⣿⣷⣹⣿
⣿⣿⣿⢟⣽⣾⣿⣿⣿⣿⣿⣿⢸⣿⣿⣿⣿⢸⡟⣟⣻⣽⣛⣯⢧⡬⢡⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣃⢹⣿⣿⣿⣿⣧⢿
⣿⢟⣥⣟⡻⢿⣿⣿⣿⣿⣿⣿⡇⣿⣿⣿⣿⢸⡽⡯⠷⠫⠹⣞⣯⢃⣯⣭⣽⣛⠿⣿⣿⡿⣟⣛⣿⣭⣷⠶⣿⣛⣯⡄⠿⣿⣿⣿⣿⣞
⡿⣐⢿⣿⣿⣷⣮⣝⢿⣿⣿⡿⣟⡸⡏⢿⣿⡨⢖⡜⣣⢟⡈⡷⢯⠸⠿⣿⣿⣿⣿⣶⣭⡻⢽⣿⣷⣶⣿⡿⢟⠻⢿⠇⣷⣝⠿⣿⣿⣧
⣧⣏⢻⠎⠝⠻⣿⣿⣷⠽⠫⣚⣭⣶⣅⢦⡟⡃⣏⢞⡵⣁⠶⡝⣻⣌⣟⢲⣾⣭⣟⣻⠿⣿⡿⣙⡛⠭⠵⣒⣢⣬⣶⣿⣿⣿⣷⣽⡛⣽
⣿⣿⣿⣾⣮⣯⣶⣽⣥⣶⣿⣿⣿⣿⣿⣿⡇⣳⢮⡹⢖⠃⣥⣛⠣⢟⣾⣣⢶⢩⣥⡭⣞⣶⣺⡽⣌⡿⠿⢍⣁⣽⣿⣿⣿⣿⣿⣿⣿⣾
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢹⡱⣎⢗⢯⠂⠶⠯⢹⣿⣶⣶⣭⡄⣗⣛⡽⠶⢯⣽⢘⣛⣛⣛⣫⣽⣿⣿⣿⣿⣿⣿⡟⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢰⢣⣏⠾⣩⢟⡐⢎⣿⣿⣿⣿⣿⡇⣟⣻⣾⣿⣿⣿⣷⡯⠭⠭⣍⣸⣿⡿⠿⣛⡉⡛⣣⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣮⣓⠮⣝⡳⢮⡝⢸⣿⣿⣿⣿⣿⣿⢸⣿⣿⣿⣿⣿⣿⣷⣭⣭⣭⣭⣶⣾⢸⡱⣃⣘⠿⠿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡯⣗⢮⣛⣬⠳⣇⡻⢸⣿⣿⣿⣿⣿⣿⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢰⡹⣕⢮⣛⣿
*/

namespace goose::platform::gWin32
{
    gWin32_DirectWrite::gWin32_DirectWrite()
    {
        HRESULT hResult = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(_factory.GetAddressOf()));
        if(FAILED(hResult)) { printf("GooseUI: Faild to create DirectWriteFactory \n"); }
    }

    bool gWin32_DirectWrite::load(const std::string& path, int pixelSize)
    {
        _size = (float)pixelSize;

        HRESULT hResult = _factory->CreateFontFileReference(std::wstring(path.begin(), path.end()).c_str(), nullptr, &_fontFile);
        if(FAILED(hResult)) { return false; }

        BOOL supported = false; // WHAT IS THE DIFFERENCE AGHAHGAHG
        UINT32 numberOfFaces;
        DWRITE_FONT_FILE_TYPE fileType;
        DWRITE_FONT_FACE_TYPE faceType;

        _fontFile->Analyze(&supported, &fileType, &faceType, &numberOfFaces);
        if(!supported) { return false; }
        
        hResult = _factory->CreateFontFace(faceType, 1, _fontFile.GetAddressOf(), 0, DWRITE_FONT_SIMULATIONS_NONE, &_face);
        if(FAILED(hResult)) { return false; }

        _initialized = true;
        return true;
    }

    const graphics::font::glyph& gWin32_DirectWrite::getGlyph(uint32_t codepoint)
    {
        if(!_initialized) { printf("GooseUI: Font not Loaded before use \n"); static graphics::font::glyph empty{}; return empty; }

        std::unordered_map<uint32_t, graphics::font::glyph>::iterator iterator = _glyphs.find(codepoint);
        if(iterator != _glyphs.end()) { return iterator->second; }

        // Map point to index then get metrics
        UINT16 index = 0;
        HRESULT hResult = _face->GetGlyphIndicesA(&codepoint, 1, &index);
        if(FAILED(hResult) || index == 0) { index = 0; }

        DWRITE_GLYPH_METRICS glyphMetrics{};
        DWRITE_FONT_METRICS fontMetrics{};
        _face->GetDesignGlyphMetrics(&index, 1, &glyphMetrics);
        _face->GetMetrics(&fontMetrics);
        
        float scale = _size / static_cast<float>(fontMetrics.designUnitsPerEm);

        int bitmapWidth = static_cast<int>((glyphMetrics.leftSideBearing + glyphMetrics.advanceWidth + glyphMetrics.rightSideBearing) * scale);
        if(bitmapWidth <=0) { bitmapWidth = 1; }

        int bitmapHeight = static_cast<int>((fontMetrics.ascent + fontMetrics.descent + fontMetrics.lineGap) * scale);
        if(bitmapHeight <= 0) { bitmapHeight = 1; };

        // Rasterize
        Microsoft::WRL::ComPtr<IDWriteGlyphRunAnalysis> analysis;
        DWRITE_MATRIX transform = { 1.0f, 0, 0, -1.0f, 0, 0 };
        DWRITE_GLYPH_RUN dRun = {};
        dRun.fontFace = _face.Get();
        dRun.fontEmSize = _size;
        dRun.glyphCount = 1;
        dRun.glyphIndices = &index;

        hResult = _factory->CreateGlyphRunAnalysis(
            &dRun,
            1.0f,
            &transform,
            DWRITE_RENDERING_MODE_ALIASED,
            DWRITE_MEASURING_MODE_NATURAL, 
            0,
            0,
            &analysis
        );
        if(FAILED(hResult)) { printf("GooseUI: Faild to create Glyph Analysis \n"); static graphics::font::glyph empty{}; return empty; }
        
        // Create the Outline
        RECT bounds;
        analysis->GetAlphaTextureBounds(DWRITE_TEXTURE_ALIASED_1x1, &bounds);

        int width = bounds.right - bounds.left;
        int height = bounds.bottom - bounds.top;
        if(width <= 0 || height <= 0) { static graphics::font::glyph empty{}; return empty; }

        std::vector<BYTE> bitmap(width * height);
        analysis->CreateAlphaTexture(DWRITE_TEXTURE_ALIASED_1x1, &bounds, bitmap.data(), (UINT32)bitmap.size());
        
        float u0, u1, v0, v1;
        _atlas.addNewBitmap(width, height, bitmap.data(), u0, u1, v0, v1);

        // Cache
        graphics::font::glyph t_glyph;
        t_glyph.u0 = u0;
        t_glyph.u1 = u1;
        t_glyph.v0 = v0;
        t_glyph.v1 = v1;
        t_glyph.width = (float)width;
        t_glyph.height = (float)height;
        t_glyph.xAdvance = (float)(glyphMetrics.advanceWidth * scale);
        t_glyph.xOffset = (float)(glyphMetrics.leftSideBearing * scale);
        t_glyph.yOffset = (float)(fontMetrics.ascent * scale);

        _glyphs[codepoint] = t_glyph;
        return _glyphs[codepoint];
    }

    graphics::font::atlas* gWin32_DirectWrite::getAtlas() { return &_atlas; }
}