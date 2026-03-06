#ifndef _GOOSEUI_GL_SHADERS_H_
#define _GOOSEUI_GL_SHADERS_H_

namespace GooseUI
{
    namespace graphics
    {
        namespace gl
        {
            static const char* texture_vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec2 aPos;
            layout(location = 1) in vec2 aTexCoords;
            layout(location = 2) in vec4 aColor;
            
            out vec2 TexCoords;
            out vec4 vColor;
            
            void main() {
                gl_Position = vec4(aPos, 0.0, 1.0);
                TexCoords = aTexCoords;
                vColor = aColor;
            }
            )";
            
            static const char* texture_fragmentSrc = R"(
            #version 330 core
            in vec2 TexCoords;
            in vec4 vColor;
            out vec4 FragColor;
            
            uniform sampler2D text;
            
            void main() {
                float alpha = texture(text, TexCoords).r;
                FragColor = vec4(vColor.rgb, alpha);
            }
            )";
            
            static const char* basic_vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec2 aPos;
            layout(location = 1) in vec4 aColor;
            
            out vec4 vColor;
            
            void main() {
                gl_Position = vec4(aPos, 0.0, 1.0);
                vColor = aColor;
            }
            )";
            
            static const char* basic_fragmentSrc = R"(
            #version 330 core
            in vec4 vColor;
            out vec4 FragColor;
            
            void main() {
                FragColor = vColor;
            }
            )";
        }
    }
}

#endif /*_GOOSEUI_GL_SHADERS_H_*/