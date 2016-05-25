//
//  RenderContext.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 8/3/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include "RenderContext.h"

RenderContext RenderContext::rc;

bool RenderContext::isValid() const
{
    return positionHandle != VERTEX_HANDLE_NONE && colorHandle != VERTEX_HANDLE_NONE;
}

void RenderContext::setProgramHandle(GLuint handle)
{
    programHandle = handle;
}

GLuint RenderContext::getProgramHandle() const
{
    return programHandle;
}

GLuint RenderContext::getPositionHandle() const
{
    return positionHandle;
}

void RenderContext::setPositionHandle(GLuint handle)
{
    if (handle != VERTEX_HANDLE_NONE)
    {
        glEnableVertexAttribArray(handle);
    }
    else if (positionHandle != VERTEX_HANDLE_NONE)
    {
        glDisable(positionHandle);
    }

    positionHandle = handle;
}

GLuint RenderContext::getColorHandle() const
{
    return colorHandle;
}

void RenderContext::setColorHandle(GLuint handle)
{
    if (handle != VERTEX_HANDLE_NONE)
    {
        glEnableVertexAttribArray(handle);
    }
    else if (colorHandle != VERTEX_HANDLE_NONE)
    {
        glDisable(colorHandle);
    }

    colorHandle = handle;
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

void RenderContext::applyProjectionMatrix()
{
    GLint projectionUniform = glGetUniformLocation(programHandle, "Projection");

    glUniformMatrix4fv(projectionUniform, 1, 0, projectionMatrix.getPointer());
}

Vertex RenderContext::UnProject(float screenX, float screenY, float screenZ) const
{
    Vertex outVec;
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

    outVec.setPosition((2*(screenX - viewport[0])/viewport[2]) - 1, (2*(viewport[1] - screenY)/viewport[3]) - 1, 2*screenZ - 1);
    outVec.multiplyByMatrix(inv);

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
