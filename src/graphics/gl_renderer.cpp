#include "GooseUI/graphics/gl_renderer.h"
#include "GooseUI/graphics/gl_loader.h"

#include <stdio.h>


static const char* vertexSrc = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec4 aColor;

out vec4 vColor;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    vColor = aColor;
}
)";

static const char* fragmentSrc = R"(
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

    void glRenderer::beginFrame(int windowWidth, int windowHeight, core::templates::renderBase::color color)
    {
        _windowWidth = windowWidth;
        _windowHeight = windowHeight;
        
        glClearColor(color.R, color.G, color.B, color.A);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, windowWidth, windowHeight);

        int localResolution = glGetUniformLocation(_shader, "uResolution");
        glUniform2f(localResolution, (float)windowWidth, (float)windowHeight);
    }

    void glRenderer::endFrame()
    {
        // HANDELED PER WINDOW
    }

    void glRenderer::drawRect(float X, float Y, float W, float H, const core::templates::renderBase::color& C)
    {
        float x0 = (2.0f * X) / _windowWidth - 1.0f;
        float x1 = (2.0f * (X + W)) / _windowWidth - 1.0f;
        
        float y0 =  1.0f - 2.0f * (Y) / _windowHeight;
        float y1 =  1.0f - 2.0f * (Y + H) / _windowHeight;

        float vertices[] = {
        x0, y0, C.R, C.G, C.B, C.A,
        x1, y0, C.R, C.G, C.B, C.A,
        x1, y1, C.R, C.G, C.B, C.A,
        x0, y1, C.R, C.G, C.B, C.A,
        };

        glUseProgram(_shader);
        glBindVertexArray(_vao);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void glRenderer::drawText(core::font::atlas* atlas, const std::string& text, float X, float Y, const core::templates::renderBase::color& C)
    {
        
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
            float vertices[4 * 6] = {};
            unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

            glGenVertexArrays(1, &_vao);
            glBindVertexArray(_vao);

            glGenBuffers(1, &_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), nullptr, GL_DYNAMIC_DRAW);

            glGenBuffers(1, &_ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            _shader = _createShaderProgram(vertexSrc, fragmentSrc);

            glBindVertexArray(0);
        }
    }

    glRenderer::~glRenderer()
    {
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
        glDeleteVertexArrays(1, &_vao);
        glDeleteProgram(_shader);
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