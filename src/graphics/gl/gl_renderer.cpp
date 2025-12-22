#include "GooseUI/graphics/gl/gl_renderer.h"
#include "GooseUI/graphics/gl/gl_loader.h"

#include "GooseUI/graphics/font/fontAtlas.h"

#include <stdio.h>

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

namespace goose::graphics::gl // EXTERNAL
{
    int glRenderer::hasContext() { return _context != nullptr; };
    glContext& glRenderer::getContext() { return *_context; }
    void glRenderer::setContext(glContext* context) { _context = context; }

    glRenderer& glRenderer::getRenderer()
    {
        static glRenderer instance;
        return instance;
    }
    
    void glRenderer::uploadFontAtlas(graphics::font::atlas& atlas)
    {
        if(atlas.isUploaded()) { return; }
        if(atlas.getID() == 0)
        {
            unsigned int id;
            glGenTextures(1, &id);
            atlas.setID(id);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, atlas.getID());

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, 0x8E42, GL_RED);
        glTexParameteri(GL_TEXTURE_2D, 0x8E43, GL_RED);
        glTexParameteri(GL_TEXTURE_2D, 0x8E44, GL_RED);
        glTexParameteri(GL_TEXTURE_2D, 0x8E45, GL_RED);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, atlas.getWidth(), atlas.getHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, atlas.getPixels().data());

        atlas.uploaded();
    }

    void glRenderer::beginFrame(int windowWidth, int windowHeight, const core::types::color& color)
    {
        _windowWidth = windowWidth;
        _windowHeight = windowHeight;
    
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glClearColor(color.R, color.G, color.B, color.A);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, windowWidth, windowHeight);

        int localResolution = glGetUniformLocation(_basicShader.shader, "uResolution");
        glUniform2f(localResolution, (float)windowWidth, (float)windowHeight);
    }

    void glRenderer::endFrame()
    {
        // HANDELED PER WINDOW
    }

    void glRenderer::drawTextureQuad(unsigned int ID, float X, float Y, float W, float H, float u0, float u1, float v0, float v1, const core::types::color& C)
    {
        float x0 = (2.0f * X) / _windowWidth - 1.0f;
        float x1 = (2.0f * (X + W)) / _windowWidth - 1.0f;
        float y0 = 1.0f - 2.0f * Y / _windowHeight;
        float y1 = 1.0f - 2.0f * (Y + H) / _windowHeight;

        float vertices[6][8] = {
            { x0, y0, u0, v0, C.R, C.G, C.B, C.A },
            { x1, y0, u1, v0, C.R, C.G, C.B, C.A },
            { x0, y1, u0, v1, C.R, C.G, C.B, C.A },

            { x1, y0, u1, v0, C.R, C.G, C.B, C.A },
            { x1, y1, u1, v1, C.R, C.G, C.B, C.A },
            { x0, y1, u0, v1, C.R, C.G, C.B, C.A },
        };

        glUseProgram(_textureShader.shader);
        glBindVertexArray(_textureShader.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ID);
    
        GLint texLocation = glGetUniformLocation(_textureShader.shader, "text");
        glUniform1i(texLocation, 0);

        glBindBuffer(GL_ARRAY_BUFFER, _textureShader.vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void glRenderer::drawRect(float X, float Y, float W, float H, const core::types::color& C)
    {
        float x0 = (2.0f * X) / _windowWidth - 1.0f;
        float x1 = (2.0f * (X + W)) / _windowWidth - 1.0f;
    
        float y0 = 1.0f - 2.0f * Y / _windowHeight;
        float y1 = 1.0f - 2.0f * (Y + H) / _windowHeight;

        float vertices[] = {
            x0, y0, C.R, C.G, C.B, C.A,
            x1, y0, C.R, C.G, C.B, C.A,
            x1, y1, C.R, C.G, C.B, C.A,
            x0, y1, C.R, C.G, C.B, C.A,
        };

        glUseProgram(_basicShader.shader);
        glBindVertexArray(_basicShader.vao);

        glBindBuffer(GL_ARRAY_BUFFER, _basicShader.vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

namespace goose::graphics::gl // INTERAL
{
    glRenderer::glRenderer()
    {
        // My rule is that functions from gl_renderer MUST have gl::* infront
        // But any functions pulled from the lib do not require gl::* infront
        if(!gl::isloaded()) { gl::loadGL(); printf("[GooseUI] Initilizing OpenGL \n"); }
        
        // initilize Resources
        if(!_context)
        {
            // Basic
            glGenVertexArrays(1, &_basicShader.vao);
            glBindVertexArray(_basicShader.vao);

            glGenBuffers(1, &_basicShader.vbo);
            glBindBuffer(GL_ARRAY_BUFFER, _basicShader.vbo);
            glBufferData(GL_ARRAY_BUFFER, 4 * 6 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

            unsigned int indices[] = {0, 1, 2, 2, 3, 0};
            glGenBuffers(1, &_basicShader.ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _basicShader.ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            _basicShader.shader = _createShaderProgram(basic_vertexSrc, basic_fragmentSrc);
            glBindVertexArray(0);

            // Texture
            glGenVertexArrays(1, &_textureShader.vao);
            glBindVertexArray(_textureShader.vao);

            glGenBuffers(1, &_textureShader.vbo);
            glBindBuffer(GL_ARRAY_BUFFER, _textureShader.vbo);
            glBufferData(GL_ARRAY_BUFFER, 6 * 8 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
            glEnableVertexAttribArray(2);

            _textureShader.shader = _createShaderProgram(texture_vertexSrc, texture_fragmentSrc);
            glBindVertexArray(0);
        }
    }

    glRenderer::~glRenderer()
    {
        glDeleteBuffers(1, &_textureShader.vbo);
        glDeleteBuffers(1, &_textureShader.ebo);
        glDeleteVertexArrays(1, &_textureShader.vao);
        glDeleteProgram(_textureShader.shader);

        glDeleteBuffers(1, &_textureShader.vbo);
        glDeleteBuffers(1, &_textureShader.ebo);
        glDeleteVertexArrays(1, &_textureShader.vao);
        glDeleteProgram(_textureShader.shader);
    }

    unsigned int glRenderer::_compileShader(const std::string& shader, unsigned int type)
    {
        unsigned int shaderID = glCreateShader(type);
        const char* c_shader = shader.c_str();

        glShaderSource(shaderID, 1, &c_shader, nullptr);
        glCompileShader(shaderID);

        int completed;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &completed);
        if(!completed)
        {
            char infoLog[512];
            glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
            printf("[GooseUI] Shader compile error: %s", infoLog);
        }

        return shaderID;
    }

    unsigned int glRenderer::_createShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int compiledVertexShader = _compileShader(vertexShader, GL_VERTEX_SHADER);
        unsigned int compiledFragmentShader = _compileShader(fragmentShader, GL_FRAGMENT_SHADER);
        unsigned int program = glCreateProgram();

        glAttachShader(program, compiledVertexShader);
        glAttachShader(program, compiledFragmentShader);

        glLinkProgram(program);

        glDeleteShader(compiledVertexShader);
        glDeleteShader(compiledFragmentShader);

        return program;
    }
}