
#ifndef _SHADER_PROGRAM_H_GL
#define _SHADER_PROGRAM_H_GL

//ToDO: Optimize includes.
#include <stdio.h>
#include <stdlib.h>
#include <GLES/gl.h>

#define GL_GLEXT_PROTOTYPES
#include <GLES/glext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "log.h"


class ShaderProgram
{
public:
    ShaderProgram(const char* vertex,const char* fragment);
    ~ShaderProgram();

    void setAttribute(const float* v, const char* name, int size);
    void setUniform(const unsigned char* pBuffer, int width, int height, const char * name, GLenum textureUnit);

private:
    GLuint programHandle;
    GLuint textureID;

    void attachShaders(GLuint vertexShader, GLuint fragmentShader);
};

#endif
