#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/glext.h>
#include <iostream>


#ifdef _DEBUG
#define GL_CALL(function) \
{ \
    function; \
    GLenum  err = glGetError(); \
    while (err != GL_NO_ERROR)  \
    { \
        std::cout << "Error in " << #function << " (Error=" << err  << ")" << std::endl; \
        err = glGetError(); \
    } \
};
#else
#define GL_CALL(function) function;
#endif // DEBUG



//Shaders
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
// Program
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;

extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

// Buffers
extern PFNGLBUFFERDATAPROC    glBufferData;
extern PFNGLBINDBUFFERPROC    glBindBuffer;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLGENBUFFERSPROC    glGenBuffers;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSAPPLEPROC glDeleteVertexArrays;

//Vertex attributes
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

//Texture
extern PFNGLACTIVETEXTUREPROC glActiveTexture;


class OpenGl
{
public:
    static void Initialize();
};

