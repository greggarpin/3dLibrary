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

class VertexAttribHandle
{
public:
    inline VertexAttribHandle() { handle = VERTEX_HANDLE_NONE; };

    inline void set(GLint pHandle) { handle = pHandle; };
    inline GLint get() const { return handle; };

    inline void enable() const { if (handle != VERTEX_HANDLE_NONE) glEnableVertexAttribArray(handle); };
    inline void disable() const { if (handle != VERTEX_HANDLE_NONE) glDisable(handle); };

private:
    GLint handle;
};

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

    inline void setPositionHandle(GLuint handle) { positionHandle.set(handle); };
    inline GLuint getPositionHandle() const { return positionHandle.get(); };
    inline void enablePositionHandle() const { positionHandle.enable(); };
    inline void disablePositionHandle() const { positionHandle.disable(); };

    inline void setColorHandle(GLuint handle) { colorHandle.set(handle); };
    inline GLuint getColorHandle() const { return colorHandle.get(); };
    inline void enableColorHandle() const { colorHandle.enable(); };
    inline void disableColorHandle() const { colorHandle.disable(); };

    inline void setNormalHandle(GLuint handle) { normalHandle.set(handle); };
    inline GLuint getNormalHandle() const { return normalHandle.get(); };
    inline void enableNormalHandle() const { normalHandle.enable(); };
    inline void disableNormalHandle() const { normalHandle.disable(); };

    inline void setTextureCoordHandle(GLuint handle) { textureCoordHandle.set(handle); };
    inline GLuint getTextureCoordHandle() const { return textureCoordHandle.get(); };
    inline void enableTextureCoordHandle() const { textureCoordHandle.enable(); };
    inline void disableTextureCoordHandle() const { textureCoordHandle.disable(); };

    void setWidth(int width);
    int getWidth() const;

    void setHeight(int height);
    int getHeight() const;

    void applyModelviewMatrix();
    void applyProjectionMatrix();
    void applySelectionId(unsigned int selectionId);
    void applyLightColor(float r, float g, float b) const;
    void applyLightPosition(float x, float y, float z, bool normalize) const;

    void enableTexturing(bool enable = true) const;
    inline void disableTexturing() const { enableTexturing(false); }

    void enableLighting(bool enable = true) const;
    inline void disableLighting() const { enableLighting(false); }

    unsigned int getSelectionIdAt(unsigned int x, unsigned int y) const;

    void pushMatrix();
    void popMatrix();

    Matrix modelviewMatrix;
    Matrix projectionMatrix;

    Vector UnProject(float screenX, float screenY, float screenZ) const;

private:
    // Singleton - no public constructor
    RenderContext() : matrixStack(MATRIX_STACK_SIZE) {};

    GLuint programHandle;
    VertexAttribHandle positionHandle;
    VertexAttribHandle colorHandle;
    VertexAttribHandle normalHandle;
    VertexAttribHandle textureCoordHandle;

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
