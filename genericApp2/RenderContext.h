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
#include "TestSled.h"

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

    void setNormalHandle(GLuint handle);
    GLuint getNormalHandle() const;

    void setWidth(int width);
    int getWidth() const;

    void setHeight(int height);
    int getHeight() const;

    bool isValid() const;

    void applyModelviewMatrix();
    void applyProjectionMatrix();
    void applySelectionId(unsigned int selectionId);
    void applyLightColor(float r, float g, float b) const;
    void applyLightPosition(float x, float y, float z, bool normalize) const;

    void enableLighting(bool enable = true) const;
    void disableLighting() const { enableLighting(false); }

    unsigned int getSelectionIdAt(unsigned int x, unsigned int y) const;

    void pushMatrix();
    void popMatrix();

    Matrix modelviewMatrix;
    Matrix projectionMatrix;

    Vector UnProject(float screenX, float screenY, float screenZ) const;

private:
    // Singleton - no public constructor
    RenderContext() : positionHandle(0), colorHandle(0), matrixStack(MATRIX_STACK_SIZE) {};

    GLuint programHandle;
    GLuint positionHandle;
    GLuint colorHandle;
    GLuint normalHandle;

    int width, height;

    static RenderContext rc;

    Stack<Matrix*> matrixStack;
};


class RenderContextTestSled : public TestSled
{
public:
    void test();
};

#endif /* defined(__genericApp2__RenderContext__) */
