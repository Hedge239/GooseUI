#ifndef _GOOSEUI_GL_SHADERS_H_
#define _GOOSEUI_GL_SHADERS_H_

namespace GooseUI
{
    namespace graphics
    {
        namespace gl
        {
            static const char* shared_vertexSrc = R"(
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

            static const char* shared_fragmentSrc = R"(
            #version 330 core
            in vec2 TexCoords;
            in vec4 vColor;
            out vec4 FragColor;
            
            uniform sampler2D u_Texture;
            uniform float u_UseTexture; // 1.0 = Use texture alpha (Text/Images), 0.0 = Use flat color
            
            void main() {
                float textAlpha = texture(u_Texture, TexCoords).r;
                
                // If u_UseTexture is 0.0, targetAlpha becomes 1.0 (ignores texture)
                // If u_UseTexture is 1.0, targetAlpha becomes textAlpha
                float targetAlpha = mix(1.0, textAlpha, u_UseTexture);
                
                FragColor = vec4(vColor.rgb, vColor.a * targetAlpha);
            }
            )";
        }
    }
}

#endif /*_GOOSEUI_GL_SHADERS_H_*/