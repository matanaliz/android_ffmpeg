#ifndef _RENDER_H
#define _RENDER_H

#include <jni.h>
#include <android/log.h>
#include <GLES/gl.h>

#define GL_GLEXT_PROTOTYPES
#include <GLES/glext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "ShaderProgram.h"

class Render
{
    public: 
        Render();
        ~Render();
        
        int init (int width, int height);
        int draw (void);
        //int getBuffer(unsigned char* buffer);
        int setTexture(const unsigned char* buf, int width, int height);
        
    private:
        void checkGlError(const char* op);
        
        unsigned char* pBuffer;
        int mWidth;
        int mHeight;
        
        ShaderProgram* shaderProgram;
    
};

#endif //_RENDER_H
