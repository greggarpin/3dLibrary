//
//  RenderingEngine1.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 7/16/15.
//  Copyright (c) 2015 Arpin, Gregg. All rights reserved.
//

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <cmath>
#include <iostream>
#include "IRenderingEngine.h"
#include "Polygon.h"
#include "Cube.h"
#include "Landscape.h"
#include "RenderContext.h"
#include "Matrix.h"
#include "Vector.h"
#include "Util.h"

#define STRINGIFY(A) #A
#include "shaders/Simple.vert"
#include "shaders/Selection.vert"
#include "shaders/Simple.frag"

class ShaderProgram {
public:
    ShaderProgram()
    {
        vertShaderHandle = fragShaderHandle = progHandle = 0;
    };
    void Build(const char *vertexShaderSource, const char *fragmentShaderSource)
    {
        GLuint vertexShader = BuildShader(vertexShaderSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = BuildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        progHandle = glCreateProgram();
        RenderContext::getMutableContext()->setProgramHandle(progHandle);

        glAttachShader(progHandle, vertexShader);
        glAttachShader(progHandle, fragmentShader);
        glLinkProgram(progHandle);

        GLint linkSuccess;
        glGetProgramiv(progHandle, GL_LINK_STATUS, &linkSuccess);

        if (linkSuccess == GL_FALSE) {
            GLchar messages[256];
            glGetProgramInfoLog(progHandle, sizeof(messages), 0, &messages[0]);
            std::cout << messages;
            exit(1);
        }
    }
    static ShaderProgram *GetActiveProgram()
    {
        return activeProgram;
    }
    void Use()
    {
        glUseProgram(progHandle);
        RenderContext::getMutableContext()->setProgramHandle(progHandle);
        ShaderProgram::activeProgram = this;
    }
    inline GLuint GetAttribLocation(const char *handleName)
    {
        return glGetAttribLocation(progHandle, handleName);
    }
    inline GLuint GetUniformLocation(const char *handleName)
    {
        return glGetUniformLocation(progHandle, handleName);
    }
private:
    GLuint vertShaderHandle, fragShaderHandle, progHandle;
    static ShaderProgram *activeProgram;

    GLuint BuildShader(const char *source, GLenum shaderType) const
    {
        GLuint shaderHandle = glCreateShader(shaderType);
        glShaderSource(shaderHandle, 1, &source, 0);
        glCompileShader(shaderHandle);

        GLint compileSuccess;
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
        if (compileSuccess == GL_FALSE) {
            GLchar messages[256];
            glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
            std::cout << messages;
            exit(1);
        }
        
        return shaderHandle;
    }

};

ShaderProgram *ShaderProgram::activeProgram = NULL;

class RenderingEngine2 : public IRenderingEngine {
public:
    RenderingEngine2();
    void Initialize(int width, int height);
    void Render() const;
    void UpdateAnimation(float timeStep) {}
    void OnRotate(DeviceOrientation orientation) {}
    void Rotate(float deltaXRad, float deltaYRad, float deltaZRad);
    void SetRotation(float xRad, float yRad, float zRad);
    void SetRotationX(float rad) { SetRotation(rad, yRot, zRot); };
    void SetRotationY(float rad) { SetRotation(xRot, rad, zRot); };
    void SetRotationZ(float rad) { SetRotation(xRot, yRot, rad); };
    void SetRoll(float rad);
    void SetPitch(float rad);
    void SetYaw(float rad);

    void onTouchStart(int x, int y);
    void onTouchMoved(int x, int y);
    void onTouchEnd(int x, int y);
    void onTap(int x, int y);

private:
    GLuint BuildShader(const char *source, GLenum shaderType) const;
    GLuint BuildProgram(const char *vertShader, const char *fragShader) const;
    void ApplyOrtho(float maxX, float maxY) const;
    void ApplyPerspective(float near, float far, float left, float right, float top, float bottom);
    void ApplyRotation() const;
    Vertex GetViewDirection() const;
    void GetWorldCoordFromScreenCoord(int screenX, int screenY, float worldHeight) const;
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
    GLuint m_depthbuffer;
    ShaderProgram normalProgram, selectionProgram;
    float xRot, yRot, zRot;
    float roll, pitch, yaw;
    bool useRollPitchYaw;
    int touchX, touchY;
    int numTouchMoves;
    bool touchStarted;
    float cameraPosition[3];

    Polygon testPolygon;
    Cube testCube;
};

void dotests()
{
    MatrixTestSled mts;
    mts.test();

    VectorTestSled vts;
    vts.test();
}
IRenderingEngine* CreateRenderer2()
{
    if (1)
        dotests();

    return new RenderingEngine2();
}

RenderingEngine2::RenderingEngine2()
{
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

    glGenRenderbuffers(1, &m_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);

    xRot = yRot = zRot = 0;
    roll = pitch = yaw = 0;
    touchStarted = false;
    numTouchMoves = 0;
    useRollPitchYaw = true;

    cameraPosition[0] = 0;
    cameraPosition[1] = 48;
    cameraPosition[0] = 0;
}

void RenderingEngine2::Initialize(int width, int height)
{
int tw, th;
glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &tw);
glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &th);
////    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderbuffer);
/*
    // Create and enable depth buffer testing
    glGenRenderbuffers(1, &m_depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, tw, th);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthbuffer);

    glEnable(GL_DEPTH_TEST);
*/
    RenderContext::getMutableContext()->setWidth(width);
    RenderContext::getMutableContext()->setHeight(height);

    glViewport(0, 0, width, height);

    normalProgram.Build(SimpleVertexShader, SimpleFragmentShader);
    selectionProgram.Build(SelectionVertexShader, SimpleFragmentShader);

    selectionProgram.Use();
    ApplyRotation();
    ApplyPerspective(-1, 10, -2, 2, -3, 3);

    normalProgram.Use();

    ApplyRotation();
//    ApplyOrtho(2, 3);
    ApplyPerspective(-1, 10, -2, 2, -3, 3);
}

RenderMode renderMode = wireframe;
void RenderingEngine2::Render() const
{
    GLuint positionSlot;
    GLuint colorSlot;
    if (renderMode == selection)
    {
    }
    positionSlot = ShaderProgram::GetActiveProgram()->GetAttribLocation("Position");
    colorSlot = ShaderProgram::GetActiveProgram()->GetAttribLocation("SourceColor");

    glClearColor(0.2,0.2,0.2,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderContext::getMutableContext()->setPositionHandle(positionSlot);
    RenderContext::getMutableContext()->setColorHandle(colorSlot);

    Landscape::getLandscape()->render(renderMode);

    ApplyRotation();

    testCube.render(renderMode);
/*
    Matrix o(RenderContext::getContext()->modelviewMatrix);
    Matrix m;
    float taxis[3] = {0, 1, 0};
    m.makeRotationMatrix(taxis, 2*PI/3);
    RenderContext::getMutableContext()->modelviewMatrix.multiply(m);
    RenderContext::getMutableContext()->applyModelviewMatrix();
        testCube.render(renderMode);
    RenderContext::getMutableContext()->modelviewMatrix.set(o);
    m.makeRotationMatrix(taxis, -2*PI/3);
    RenderContext::getMutableContext()->modelviewMatrix.multiply(m);
    RenderContext::getMutableContext()->applyModelviewMatrix();
        testCube.render(renderMode);
    RenderContext::getMutableContext()->modelviewMatrix.set(o);
*/
    RenderContext::getMutableContext()->setPositionHandle(VERTEX_HANDLE_NONE);
    RenderContext::getMutableContext()->setColorHandle(VERTEX_HANDLE_NONE);
}

void RenderingEngine2::ApplyOrtho(float maxX, float maxY) const
{
    float a = 1.0/maxX;
    float b = 1.0/maxY;

    RenderContext::getMutableContext()->projectionMatrix.set(
                    a, 0, 0, 0,
                    0, b, 0, 0,
                    0, 0, -1, 0,
                    0, 0, 0, 1);
    RenderContext::getMutableContext()->applyProjectionMatrix();
}

void RenderingEngine2::ApplyPerspective(float near, float far, float left, float right, float top, float bottom)
{
    float a = 2*near/(right - left);
    float b = 2*near/(top - bottom);
    float c = (right+left)/(right - left);
    float d = (top+bottom)/(top - bottom);
    float e = (far+ near)/(far - near);
    float f = -2*far*near/(far - near);

    RenderContext::getMutableContext()->projectionMatrix.set(
        a,  0,  0,  0,
        0,  b,  0,  0,
        c,  d,  e,  -1,
        0,  0,  f,  1);

    RenderContext::getMutableContext()->applyProjectionMatrix();
}

void RenderingEngine2::Rotate(float deltaXRad, float deltaYRad, float deltaZRad)
{
    xRot += deltaXRad;
    CLAMP_RAD(xRot);
    
    yRot += deltaYRad;
    CLAMP_RAD(yRot);

    zRot += deltaZRad;
    CLAMP_RAD(zRot);
}

void RenderingEngine2::SetRotation(float xRad, float yRad, float zRad)
{
    xRot = xRad;
    yRot = yRad;
    zRot = zRad;
}

void RenderingEngine2::ApplyRotation() const
{
    Matrix m;

    static float xAxis []  = {1, 0, 0};
    static float yAxis []  = {0, 1, 0};
    static float zAxis []  = {0, 0, 1};

    RenderContext::getMutableContext()->modelviewMatrix.makeIdentityMatrix();

    if (!useRollPitchYaw)
    {
        m.makeRotationMatrix(xAxis, xRot);
        RenderContext::getMutableContext()->modelviewMatrix.multiply(m);

        m.makeRotationMatrix(yAxis, yRot);
        RenderContext::getMutableContext()->modelviewMatrix.multiply(m);

        m.makeRotationMatrix(zAxis, zRot);
        RenderContext::getMutableContext()->modelviewMatrix.multiply(m);
    }
    else
    {
        m.makeRotationMatrix(yAxis, yaw);
        RenderContext::getMutableContext()->modelviewMatrix.multiply(m);

        m.makeRotationMatrix(xAxis, pitch);
        RenderContext::getMutableContext()->modelviewMatrix.multiply(m);

        m.makeRotationMatrix(zAxis, roll);
        RenderContext::getMutableContext()->modelviewMatrix.multiply(m);
    }

    RenderContext::getMutableContext()->applyModelviewMatrix();
}

#define NORMALIZED_TOUCH_CHANGE_X(deltaX) (PI * ((float)deltaX) / (float)RenderContext::getContext()->getWidth())
#define NORMALIZED_TOUCH_CHANGE_Y(deltaY) (PI * ((float)deltaY) / (float)RenderContext::getContext()->getHeight())
#define TAP_MOVE_THRESHOLD 2

void RenderingEngine2::onTouchStart(int x, int y)
{
    touchStarted = true;
    numTouchMoves = 0;

    touchX = x;
    touchY = y;
}

void RenderingEngine2::onTouchMoved(int x, int y)
{
    if (!touchStarted)
        return;

    numTouchMoves++;

    if (numTouchMoves < TAP_MOVE_THRESHOLD)
        return;

    if (useRollPitchYaw)
    {
        pitch += NORMALIZED_TOUCH_CHANGE_Y(y - touchY);
        yaw += NORMALIZED_TOUCH_CHANGE_X(touchX - x);
    }
    else
    {
        Rotate(NORMALIZED_TOUCH_CHANGE_Y(y - touchY), NORMALIZED_TOUCH_CHANGE_X(touchX - x), 0);
    }

    touchX = x;
    touchY = y;
}

void RenderingEngine2::onTouchEnd(int x, int y)
{
    if (!touchStarted)
        return;

    if (numTouchMoves <= TAP_MOVE_THRESHOLD)
    {
        onTap(x, y);
        return;
    }

    touchX = x;
    touchY = y;

    touchStarted = false;
}

void RenderingEngine2::onTap(int x, int y)
{
    // TODO:: Get rid of this - only in place for validating 'onTap' logic
    renderMode = (renderMode == wireframe ? normal : wireframe);
    GetWorldCoordFromScreenCoord(x, y, 0);
}

void RenderingEngine2::SetRoll(float rad)
{
    useRollPitchYaw = true;
    roll = rad;
}
void RenderingEngine2::SetPitch(float rad)
{
    useRollPitchYaw = true;
    pitch = rad;
}
void RenderingEngine2::SetYaw(float rad)
{
    useRollPitchYaw = true;
    yaw = rad;
}

Vertex RenderingEngine2::GetViewDirection() const
{
    Vertex retValue;
    Matrix rotMatrix;
    static float xAxis []  = {1, 0, 0};
    static float yAxis []  = {0, 1, 0};
    static float zAxis []  = {0, 0, 1};

    retValue.setPosition(0, 0, 1);

    rotMatrix.makeRotationMatrix(yAxis, yaw);
    retValue.multiplyByMatrix(rotMatrix);

    rotMatrix.makeRotationMatrix(xAxis, pitch);
    retValue.multiplyByMatrix(rotMatrix);

    rotMatrix.makeRotationMatrix(zAxis, roll);
    retValue.multiplyByMatrix(rotMatrix);

    return retValue;
}

void RenderingEngine2::GetWorldCoordFromScreenCoord(int screenX, int screenY, float worldHeight) const
{
    const Vertex floorNormal(0, 1, 0);
    Vertex view = GetViewDirection();

    // If view direction is close to (less than 5 degrees from) perpendicular to (0,1,0), don't try to find floor intersection
    if (false && fabs(view.dot(floorNormal)) < 5.0 * PI/180.0)
    {
        //    Return tapPos + viewDirection*10
    }
    else
    {
        Vertex near, far;
        // Return tapPos + viewDirection intersect with P(0,1,0,worldHeight)
        near = RenderContext::getContext()->UnProject(screenX, 480-screenY, 0);
        far = RenderContext::getContext()->UnProject(screenX, 480-screenY, 1);
    }
}

