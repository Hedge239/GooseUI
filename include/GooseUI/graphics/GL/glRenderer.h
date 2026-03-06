#ifndef _GOOSEUI_GL_RENDERER
#define _GOOSEUI_GL_RENDERER

#include "GooseUI/types.h"
#include "GooseUI/abstractions/iRenderer.h"

#include <string>

#if defined(_WIN32)

    #include <windows.h>

#elif defined(__APPLE__)

    #error Unsuported // TODO

#else

    #if GOOSEUI_XORG_SUPPORT
        #include <X11/Xlib.h>
        #include <GL/glx.h>
    #endif

    #if GOOSEUI_WAYLAND_SUPPORT
        #include <wayland-client.h>
    #endif

#endif

namespace GooseUI
{
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
                
                #error Unsuported // TODO

                #endif
            };
            
            struct shader
            {
                unsigned int shader = 0;
                unsigned int vbo = 0;
                unsigned int ebo = 0;
                unsigned int vao = 0;
            };
            
            class glRenderer : public absractions::iRenderer
            {
                glContext* _context = nullptr;
                
                shader _basicShader;
                shader _textureShader;
                
                unsigned int _windowWidth = 0;
                unsigned int _windowHeight = 0;
                unsigned int _compileShader(const std::string& shader, unsigned int type);
                unsigned int _createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
                
                public:
                glRenderer();
                ~glRenderer();
                
                int hasContext();
                glContext& getContext();
                void setContext(glContext* context);
                
                // Overides
                void initRenderer() override;
                
                void beginFrame(int windowWidth, int windowHeight, const color &C) override;
                void endFrame() override;
                
                void drawRect(float X, float Y, float W, float H, const color &C) override;
                void drawTexture() override;
                void drawBitmapFont(unsigned int ID, float X, float Y, float W, float H, float u0, float u1, float v0, float v1, const color& color) override;
                void drawSdfFont() override;
            };
        }
    }
}

#endif /*_GOOSEUI_GL_RENDERER*/