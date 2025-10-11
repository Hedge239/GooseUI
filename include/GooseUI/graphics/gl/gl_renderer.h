#ifndef _GOOSEUI_GL_RENDERER_
#define _GOOSEUI_GL_RENDERER_

#include "GooseUI/core/templates/renderBase.h"

#include <string>

#if defined(_WIN32)
    #include <windows.h>
#endif

namespace goose
{
    namespace graphics
    {
        namespace font
        {
            class atlas; // FORWARD DECLERATION
        }
    }

    namespace graphics
    {
        namespace gl
        {
            struct glContext
            {
                #if defined(_WIN32)
                HGLRC hglrc = nullptr;
                HDC   hdc   = nullptr;
                #elif 
                #endif
            };

            class glRenderer : public core::templates::renderBase::renderer
            {
                glRenderer();
                ~glRenderer();

                glRenderer(const glRenderer&) = delete;
                glRenderer& operator=(const glRenderer) = delete;

                glContext* _context = nullptr;

                unsigned int _vao = 0;
                unsigned int _vbo = 0;
                unsigned int _ebo = 0;
                unsigned int _shader = 0;

                unsigned int _windowWidth = 0;
                unsigned int _windowHeight = 0;

                unsigned int _compileShader(const std::string& shader, unsigned int type);
                unsigned int _createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);

                public:
                static glRenderer& getRenderer();

                int hasContext();
                glContext& getContext();
                void setContext(glContext* context);

                // Overides
                void uploadFontAtlas(graphics::font::atlas& atlas) override;

                void beginFrame(int windowWidth, int windowHeight, core::templates::renderBase::color color) override;
                void endFrame() override;

                void drawTextureQuad(unsigned int ID, float X, float Y, float W, float H, float u0, float u1, float v0, float v1, const core::templates::renderBase::color& C) override;
                void drawRect(float X, float Y, float W, float H, const core::templates::renderBase::color& C) override;
            };
        }
    }
}

#endif /*_GOOSEUI_GL_RENDERER_*/