//
//  RenderContext.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 8/3/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include <math.h>

#include "RenderContext.h"

RenderContext RenderContext::rc;

void RenderContext::setProgramHandle(GLuint handle)
{
    programHandle = handle;
}

GLuint RenderContext::getProgramHandle() const
{
    return programHandle;
}

#define intPartToFloat(intVal, bitShift) (((intVal >> bitShift) & 0x000000FF)/255.0)

void RenderContext::applySelectionId(unsigned int selectionId)
{
    GLint selectionIdUniform = glGetUniformLocation(programHandle, "SelectionId");

    if (selectionId == 0)
    {
        glUniform4f(selectionIdUniform, 0, 0, 0, 0);
    }
    else
    {
        glUniform4f(selectionIdUniform, intPartToFloat(selectionId, 0), intPartToFloat(selectionId, 8), intPartToFloat(selectionId, 16), 1);
    }
}

unsigned int RenderContext::getSelectionIdAt(unsigned int x, unsigned int y) const
{
    GLubyte pixelColor[4] = {0, 0, 0, 0};
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixelColor);

    unsigned int retVal = (pixelColor[0] | (pixelColor[1] << 8) | (pixelColor[2] << 16));
    
    return retVal;
}

void RenderContext::applyModelviewMatrix()
{
    GLint modelviewUniform = glGetUniformLocation(programHandle, "Modelview");

    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.getPointer());

    GLint normalModelviewUniform = glGetUniformLocation(programHandle, "NormalModelview");

    // As long as we don't allow any non-uniform scaling, the normal transformation matrix
    // is the same as the regular transformation matrix.  (E.g., in practice, we only need
    // upper left 3x3 from the modelview matrix - current implementation doesn't support it
    // and it can be easily done from vertex program for now)
    glUniformMatrix4fv(normalModelviewUniform, 1, 0, modelviewMatrix.getPointer());
}

void RenderContext::setWidth(int wp)
{
    width = wp;
}

int RenderContext::getWidth() const
{
    return width;
}

void RenderContext::setHeight(int hp)
{
    height = hp;
}

int RenderContext::getHeight() const
{
    return height;
}

void RenderContext::applyLightColor(float r, float g, float b) const
{
    GLint lightColUniform = glGetUniformLocation(programHandle, "LightColor");
    glUniform3f(lightColUniform, r, g, b);
}

void RenderContext::applyLightPosition(float x, float y, float z, bool normalize) const
{
    GLint lightDirUniform = glGetUniformLocation(programHandle, "LightPosition");
    if (normalize)
    {
        float len = sqrt(x*x + y*y + z*z);
        if (len > 0)
        {
            x /= len;
            y /= len;
            z /= len;
        }
    }

    glUniform3f(lightDirUniform, x, y, z);
}

void RenderContext::enableTexturing(bool enable) const
{
    GLint texturingToggle = glGetUniformLocation(programHandle, "EnableTexturing");
    if (enable)
    {
        glUniform1f(texturingToggle, 1.0);
        enableTextureCoordHandle();
    }
    else
    {
        glUniform1f(texturingToggle, 0.0);
        disableTextureCoordHandle();
    }
}

void RenderContext::enableLighting(bool enable) const
{
    GLint lightingToggle = glGetUniformLocation(programHandle, "EnableLighting");
    glUniform1f(lightingToggle, (enable ? 1.0 : 0.0));
}

void RenderContext::enableSelectionMode(bool enable) const
{
    GLint selectionToggle = glGetUniformLocation(programHandle, "SelectionModeOn");
    glUniform1f(selectionToggle, (enable ? 1.0 : 0.0));
}
// TODO:: Shouldn't need to fetch the uniform_locations every time
void RenderContext::enableTransformations(bool enable) const
{
    GLint transformToggle = glGetUniformLocation(programHandle, "EnableTransform");
    glUniform1f(transformToggle, (enable ? 1.0 : 0.0));
}

void RenderContext::applyProjectionMatrix()
{
    GLint projectionUniform = glGetUniformLocation(programHandle, "Projection");

    glUniformMatrix4fv(projectionUniform, 1, 0, projectionMatrix.getPointer());
}

Vector RenderContext::UnProject(float screenX, float screenY, float screenZ) const
{
    Vector outVec;
    Matrix modelViewProj;
    Matrix inv;
    bool hasInverse = false;

    modelViewProj.set(projectionMatrix);
    modelViewProj.multiply(modelviewMatrix);
    hasInverse = modelViewProj.getInverse(inv);

    float viewport[4];
    viewport[0] = 0;
    viewport[1] = 0;
    viewport[2] = getWidth();
    viewport[3] = getHeight();

    outVec.set((2*(screenX - viewport[0])/viewport[2]) - 1, (2*(screenY - viewport[1])/viewport[3]) - 1, 2*screenZ - 1, 1);
    outVec.multiplyByMatrix(inv);
    outVec.setW(1);

    return outVec;
}

void RenderContext::pushMatrix()
{
    matrixStack.push(new Matrix(modelviewMatrix));
    // TODO:: Exception might be best...
    assert(matrixStack.getNumItems() <= MATRIX_STACK_SIZE);
}

void RenderContext::popMatrix()
{
    Matrix *lastMatrix = matrixStack.pop();
    assert(lastMatrix != NULL);

    modelviewMatrix.set(*lastMatrix);
}

void RenderContextTestSled::test()
{
    int oldWidth = RenderContext::getContext()->getWidth();
    int oldHeight = RenderContext::getContext()->getHeight();

    RenderContext::getMutableContext()->setWidth(100);
    RenderContext::getMutableContext()->setHeight(100);

    Vector v = RenderContext::getContext()->UnProject(50, 50, 0);

    test_fail_if(v.getX() != 0, "Unexpected X value");
    test_fail_if(v.getY() != 0, "Unexpected Y value");
    test_fail_if(v.getZ() != -1, "Unexpected Z value");

    RenderContext::getMutableContext()->setWidth(oldWidth);
    RenderContext::getMutableContext()->setHeight(oldHeight);

    test_pass;
}
