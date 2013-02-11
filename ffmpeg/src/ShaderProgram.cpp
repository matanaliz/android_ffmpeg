#include "ShaderProgram.h"

static GLuint loadShader(GLenum shaderType, const char* pSource);
static GLuint createGLtex2dFromBuffer(const unsigned char* buffer, int width, int height, GLenum texture);

               
ShaderProgram::ShaderProgram(const char* vertex, const char* fragment)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertex); 
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragment);

    programHandle = glCreateProgram();
    attachShaders(vertexShader, fragmentShader);
    
    glGenTextures(1, &textureID);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(programHandle);
};

// Uniforms

void ShaderProgram::setUniform(const unsigned char* pBuffer, int width, int height, const char * name, GLenum textureUnit)
{
    glUseProgram(programHandle);
    
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glUniform1i(glGetUniformLocation(programHandle, name), textureUnit - GL_TEXTURE0);
    
    GLint uniformHandle = glGetUniformLocation(programHandle, name);
    if (uniformHandle != -1)
        glUniform1i(glGetUniformLocation(programHandle, name), textureUnit - GL_TEXTURE0);
    else
        LOGE("SHADER PROGRAM: %s uniform didn't find", name);
    
}

void ShaderProgram::setAttribute(const float* pValue, const char* name, int size)
{
    glUseProgram(programHandle);
    GLuint gvPositionHandle = glGetAttribLocation(programHandle, name);
    glVertexAttribPointer(gvPositionHandle, size, GL_FLOAT, GL_FALSE, 0, pValue);
    glEnableVertexAttribArray(gvPositionHandle);
}

void  ShaderProgram::attachShaders(GLuint vertexShader,GLuint fragmentShader)
{
    if (programHandle) {
        glAttachShader(programHandle, vertexShader);
        glAttachShader(programHandle, fragmentShader);
        
        
        glLinkProgram(programHandle);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(programHandle, GL_LINK_STATUS, &linkStatus);

        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(programHandle, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(programHandle);
            programHandle = 0;
        }
    }
}

GLuint loadShader(GLenum shaderType, const char* pSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}



GLuint createGLtex2dFromBuffer(const unsigned char* buffer, int width, int height, GLenum texture)
{
        //~ glActiveTexture(texture);
        //~ glBindTexture(GL_TEXTURE_2D, textureID);
        //~ glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        //~ glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //~ glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
        //~ glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //~ glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //~ return textureID;
}

