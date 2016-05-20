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

