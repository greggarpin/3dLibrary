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
// TODO get viewport stuff properly
    const float viewport[4] = {0, 0, 320, 480};
    outVec.setPosition((2*(screenX - viewport[0])/viewport[2]) - 1, (2*(screenY - viewport[1])/viewport[3]) - 1, 2*screenZ - 1);
    outVec.multiplyByMatrix(inv);

    return outVec;
}