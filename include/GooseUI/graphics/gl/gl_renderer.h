#ifndef _GOOSEUI_GL_RENDERER_
#define _GOOSEUI_GL_RENDERER_

#include "GooseUI/core/templates/renderBase.h"

#include <X11/Xlib.h>
#include <string>

#if defined(_WIN32)

    #include <windows.h>

#elif defined(__APPLE__)

    #error Unsuported // TODO

#else

    #if GOOSEUI_XORG_SUPPORT
        #include <GL/glx.h>
    #endif

    #if GOOSEUI_WAYLAND_SUPPORT
        #include <wayland-client.h>
    #endif

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

                #endif
                #if defined(__APPLE__)

                #error Unsuported // TODO

                #endif
                #if GOOSEUI_XORG_SUPPORT

                GLXContext glxContext = nullptr;

                #endif
                #if GOOSEUI_WAYLAND_SUPPORT



                #endif
            };

            struct shader
            {
                unsigned int shader = 0;
                unsigned int vbo = 0;
                unsigned int ebo = 0;
                unsigned int vao = 0;
            };

            class glRenderer : public core::templates::renderBase::renderer
            {
                glRenderer();
                ~glRenderer();

                glRenderer(const glRenderer&) = delete;
                glRenderer& operator=(const glRenderer) = delete;

                glContext* _context = nullptr;

                shader _textureShader;
                shader _basicShader;

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