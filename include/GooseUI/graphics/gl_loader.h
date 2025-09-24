#ifndef _GOOSEUI_GL_LOADER_H_
#define _GOOSEUI_GL_LOADER_H_

#if defined (_WIN32)

#include <windows.h>
#include <GL/gl.h>

#elif defined (__APPLE__)

#include <dlfcn.h>
#include <OpenGL/gl3.h>

#else

#include <dlfcn.h>
#include <GL/gl.h>
#include <GL/glx.h>

#endif

#include <cstddef>

// This is pain, and yet I enjoy it - 9/6/25
// I'm only creating this so I can include system libs and it "Just Works"
// Before you think that I am a masochist, I did write all this by hand.

#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_COMPILE_STATUS 0x8B81
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_ELEMENT_ARRAY_BUFFER 0x8893

namespace goose
{
    namespace graphics
    {
        namespace gl
        {   
            // OpenGL TypeDefs
            typedef char GLchar;
            typedef unsigned int GLuint;
            typedef std::ptrdiff_t GLsizeiptr;
            typedef std::ptrdiff_t GLintptr;

            typedef GLuint(APIENTRY* PFNGLCREATESHADERPROC)(GLenum type);
            typedef GLuint(APIENTRY* PFNGLCREATEPROGRAMPROC)(void);

            typedef GLint(APIENTRY* PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar *name);

            typedef void(APIENTRY* PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
            typedef void(APIENTRY* PFNGLCOMPILESHADERPROC)(GLuint shader);
            typedef void(APIENTRY* PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
            typedef void(APIENTRY* PFNGLLINKPROGRAMPROC)(GLuint program);
            typedef void(APIENTRY* PFNGLUSEPROGRAMPROC)(GLuint program);
            typedef void(APIENTRY* PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint* buffers);
            typedef void(APIENTRY* PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint* arrays);
            typedef void(APIENTRY* PFNGLDELETEPROGRAMPROC)(GLuint program);
            typedef void(APIENTRY* PFNGLGENVERTEXARRAYSPROC)(GLsizei n, const GLuint* array);
            typedef void(APIENTRY* PFNGLBINDVERTEXARRAYPROC)(GLuint array);
            typedef void(APIENTRY* PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
            typedef void(APIENTRY* PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
            typedef void(APIENTRY* PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
            typedef void(APIENTRY* PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
            typedef void(APIENTRY* PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
            typedef void(APIENTRY* PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
            typedef void(APIENTRY* PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
            typedef void(APIENTRY* PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
            typedef void(APIENTRY* PFNGLCLEARPROC)(GLbitfield mask);
            typedef void(APIENTRY* PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
            typedef void(APIENTRY* PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
            typedef void(APIENTRY* PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices);
            typedef void(APIENTRY* PFNGLDELETESHADERPROC)(GLuint shader);
            typedef void(APIENTRY* PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);

            // OpenGL Variables
            extern PFNGLDELETESHADERPROC glDeleteShader;
            extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
            extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
            extern PFNGLGENBUFFERSPROC glGenBuffers;
            extern PFNGLBUFFERDATAPROC glBufferData;
            extern PFNGLBINDBUFFERPROC glBindBuffer;
            extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
            extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
            extern PFNGLGETSHADERIVPROC glGetShaderiv;
            extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
            extern PFNGLCLEARCOLORPROC glClearColor;
            extern PFNGLCLEARPROC glClear;
            extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
            extern PFNGLUNIFORM2FPROC glUniform2f;
            extern PFNGLUNIFORM4FPROC glUniform4f;
            extern PFNGLDRAWELEMENTSPROC glDrawElements;
            extern PFNGLCREATESHADERPROC glCreateShader;
            extern PFNGLSHADERSOURCEPROC glShaderSource;
            extern PFNGLCOMPILESHADERPROC glCompileShader;
            extern PFNGLCREATEPROGRAMPROC glCreateProgram;
            extern PFNGLATTACHSHADERPROC glAttachShader;
            extern PFNGLLINKPROGRAMPROC glLinkProgram;
            extern PFNGLUSEPROGRAMPROC glUseProgram;
            extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
            extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
            extern PFNGLDELETEPROGRAMPROC glDeleteProgram; 
            extern PFNGLBUFFERSUBDATAPROC glBufferSubData;

            // Loader Variables
            int isloaded();
            
            int loadGL();
            static void closeGL();
        }
    }
}

#endif /*_GOOSEUI_GL_LOADER_H_*/