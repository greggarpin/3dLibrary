//
//  RenderContext.h
//  genericApp2
//
//  Created by Arpin, Gregg on 8/3/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#ifndef __genericApp2__RenderContext__
#define __genericApp2__RenderContext__

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "Matrix.h"
#include "Vertex.h"
#include "Stack.h"

#define VERTEX_HANDLE_NONE -1
#define MATRIX_STACK_SIZE 16

class RenderContext
{
public:
    static RenderContext *getMutableContext()
    {
        return &rc;
    };

    static const RenderContext *getContext()
    {
        return getMutableContext();
    };

    void setProgramHandle(GLuint program);
    GLuint getProgramHandle() const;

    void setPositionHandle(GLuint handle);
    GLuint getPositionHandle() const;

    void setColorHandle(GLuint handle);
    GLuint getColorHandle() const;

    void setWidth(int width);
    int getWidth() const;

    void setHeight(int height);
    int getHeight() const;

    bool isValid() const;

    void applyModelviewMatrix();
    void applyProjectionMatrix();
    void applySelectionId(unsigned int selectionId);

    unsigned int getSelectionIdAt(unsigned int x, unsigned int y) const;

    void pushMatrix();
    void popMatrix();

    Matrix modelviewMatrix;
    Matrix projectionMatrix;

    Vertex UnProject(float screenX, float screenY, float screenZ) const;

private:
    // Singleton - no public constructor
    RenderContext() : positionHandle(0), colorHandle(0), matrixStack(MATRIX_STACK_SIZE) {};

    GLuint programHandle;
    GLuint positionHandle;
    GLuint colorHandle;

    int width, height;

    static RenderContext rc;

    Stack<Matrix*> matrixStack;
};

#endif /* defined(__genericApp2__RenderContext__) */
