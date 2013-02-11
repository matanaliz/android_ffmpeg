#include "Render.h"

static const char* vtShader = "attribute vec4 vPosition;"
            "attribute vec2 rm_TexCoord0;"
            "varying vec2 vTexCoord;"
            "void main() {"
            "   gl_Position = vPosition;"
            "   vTexCoord = rm_TexCoord0.st;"
            "}";
        
static const char* fgShader =
            "precision mediump float;"
            "varying vec2 vTexCoord;"
            "uniform sampler2D OriginTexture;\n"
            "void main() "
            "{"
            "   vec4 res;"
            "   res = vec4(1.0, 0.0, 0.0, 1.0);"
            "   res = texture2D(OriginTexture,vTexCoord);"
            "   gl_FragColor = res;"
            "} ";
            
 static float rectangleVertices[] =  {
                
                -1.0f,  1.0f,
               -1.0f, -1.0f,
               1.0f,  1.0f,
               1.0f, -1.0f
               };

 static float rectangleTexcoords[] = {
               1.0f, 0.0f,
               1.0f, 1.0f,
               0.0f, 0.0f,
               0.0f, 1.0f };  

Render::Render()
    : pBuffer(0)
    , shaderProgram(0)
{
    
}

Render::~Render()
{
    
}

int Render::init(int width, int height)
{
    shaderProgram = new ShaderProgram(vtShader, fgShader);
    glViewport(0, 0, width, height);
    
    return 1;
}

int Render::draw(void)
{
    shaderProgram->setAttribute(rectangleVertices,"vPosition", 2);
    checkGlError("shaderProgram.setAttribute vertex shader");
    shaderProgram->setAttribute(rectangleTexcoords,"rm_TexCoord0", 2);
    checkGlError("shaderProgram.setAttribute fragment shader");    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); 
    checkGlError("glDrawArrays"); 

    return 1;
}

void Render::checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGE("after %s() glError (0x%x)\n", op, error);
    }
}

int Render::setTexture(const unsigned char* pBuffer, int width, int height)
{
    shaderProgram->setUniform(pBuffer, width, height, "OriginTexture", GL_TEXTURE0);
    checkGlError("setTexture");
}
